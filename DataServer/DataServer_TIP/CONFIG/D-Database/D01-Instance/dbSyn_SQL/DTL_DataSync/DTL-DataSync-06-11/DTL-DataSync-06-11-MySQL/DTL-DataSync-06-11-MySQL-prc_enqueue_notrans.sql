DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_enqueue_notrans` $$
CREATE PROCEDURE `prc_enqueue_notrans`(
	IN   p_queue            VARCHAR(50),
  IN   p_payload_1        VARCHAR(4000),
  IN   p_payload_2        VARCHAR(4000),
  IN   p_payload_3        VARCHAR(4000),
  IN   p_msgid            VARCHAR(38),
  IN   p_sub_cnt          TINYINT(1),
  IN   p_recipient        VARCHAR(4000)	)
BEGIN
	DECLARE v_q_type			  TINYINT(1);	# 0:multi-comsumer; 1:single
# DECLARE v_enq_opt             TINYINT(1) DEFAULT 2;	 # 0: enable; 1: disable
	DECLARE v_sid                 BIGINT(20) DEFAULT 0;
	DECLARE v_priority     	  	  TINYINT(1) DEFAULT 1;
	DECLARE v_state        	  	  TINYINT(1) DEFAULT 1;  # 1: ready; 2: processing; 3: remove_delay 4: done
	DECLARE v_no_more_rows        BOOLEAN DEFAULT FALSE;
	DECLARE v_bWarn               BOOLEAN DEFAULT FALSE;
	DECLARE v_seq_name            VARCHAR(128) DEFAULT NULL;
	DECLARE v_queue_name          VARCHAR(50) DEFAULT UPPER(p_queue);
	DECLARE v_queue_tab           VARCHAR(55) DEFAULT NULL;
	DECLARE v_msgid               VARCHAR(38) DEFAULT NULL;
	-- DECLARE v_payload             VARCHAR(8080) DEFAULT NULL;
	DECLARE v_curuser_deli        VARCHAR(3) DEFAULT '@';
	declare v_enq_state 		  TINYINT(1);


	DECLARE CONTINUE HANDLER FOR NOT FOUND
		SET v_no_more_rows = TRUE;


	DECLARE CONTINUE HANDLER FOR SQLWARNING
		SET v_bWarn = TRUE;
	DECLARE CONTINUE HANDLER FOR 1062 BEGIN  END;


-- check enqueue option enable or not
	SELECT q_type, enq_state INTO v_q_type, v_enq_state FROM aq_sys_queue_m WHERE upper(q_name) = v_queue_name;

	IF v_q_type = 1 and (p_recipient <> '' or p_sub_cnt <> 0) THEN
		SIGNAL SQLSTATE '45001'
			SET MESSAGE_TEXT = 'Single-consumer AQ doesn''t allow recipient and p_sub_cnt must be 0.';
	END IF;
	
-- Modified by Will 19Oct2012, check the format of p_recipient when sub_cnt = 1.
/*
	IF  p_sub_cnt = 1 and (p_recipient is null or p_recipient = '') THEN
		SIGNAL SQLSTATE '45002'
			SET MESSAGE_TEXT = 'The p_recipient can not be null if p_sub_cnt = 1.';
	END IF;
*/
	IF  p_sub_cnt = 1 and (p_recipient is null or p_recipient = '' or instr(p_recipient,',') <= 1) THEN
		SIGNAL SQLSTATE '45002'
			SET MESSAGE_TEXT = 'Please check the format of p_recipient when p_sub_cnt = 1.';
	END IF;


/*
 Commented by Will 19Oct2012, the p_recipient will be ignored when sub_cnt = 0.
	IF p_sub_cnt = 0 and p_recipient <> '' and upper(p_recipient) <> upper(database()) THEN
		SIGNAL SQLSTATE '45003'
			SET MESSAGE_TEXT = 'It''s not my message.';
	END IF;
*/

	IF v_enq_state = 1 then
		SIGNAL SQLSTATE '45004'
			SET MESSAGE_TEXT = 'The enqueue is disable.';
  ELSEIF v_enq_state = 0 then
      -- main function
      	SET v_msgid     = UUID();
      	SET v_seq_name  = CONCAT('AQ_', v_queue_name, '_SEQ');
      	SET v_queue_tab = CONCAT(v_queue_name, '_T');
		
      --	SET v_payload   = REPLACE(p_payload, '''', '''''');
		SET p_payload_1   = REPLACE(p_payload_1, '''', '''''');
		SET p_payload_2   = REPLACE(p_payload_2, '''', '''''');
		SET p_payload_3   = REPLACE(p_payload_3, '''', '''''');
		

      	SET v_sid = func_seq_get_next_number(v_seq_name);
      	-- IF p_sub_cnt <> 0 THEN
		-- IF p_sub_cnt <> 0 or (p_sub_cnt = 0 and p_recipient <> '') THEN
		IF p_sub_cnt <> 0 THEN
      		CALL prc_enq_others(v_queue_name, v_msgid, v_sid, p_recipient);
      	END IF;
      	
		-- This if/else is used for avoid unique error of sender_msgid.
		if p_msgid = '' then
			set p_msgid = null;
		end if;
		
              SET @g_sql = CONCAT('INSERT INTO ', v_queue_tab, '(Q_NAME, MSG_SID, MSGID, PRIORITY, STATE, SUB_CNT, ENQ_TIME, ENQ_UID, SENDER_MSGID, user_data_1, user_data_2, user_data_3) VALUES (',
      							'''', v_queue_name, '''', ',', v_sid, ',','''',v_msgid,'''' ,',', v_priority, ',', v_state,',', p_sub_cnt, ', sysdate(),SUBSTRING_INDEX(CURRENT_USER, ', '''',v_curuser_deli,'''', ',1),',
      							if(p_msgid is null, 'NULL',concat('''',p_msgid,'''')),',', if(p_payload_1 is null or p_payload_1 = '', 'NULL',concat('''',p_payload_1,'''')),',',if(p_payload_2 is null or p_payload_2 = '', 'NULL',concat('''',p_payload_2,'''')),',',
								if(p_payload_3 is null or p_payload_3 = '', 'NULL',concat('''',p_payload_3,'''')),')');

      	PREPARE stmt FROM @g_sql;
      	EXECUTE stmt;
      	DEALLOCATE PREPARE stmt;
          SET @g_sql = NULL;

  END IF;
  
END $$

DELIMITER ;
