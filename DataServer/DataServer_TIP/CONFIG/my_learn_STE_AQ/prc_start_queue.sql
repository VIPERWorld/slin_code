DELIMITER $$

DROP PROCEDURE IF EXISTS `prc_start_queue` $$
CREATE PROCEDURE `prc_start_queue`(
	IN p_queue_name      VARCHAR(50),
	IN p_queue_option    TINYINT(1) )
-- p_queue_name: the name of the queue
-- p_queue_option: the functionalities options of the queue
-- 0: eable enqueue; 1: enable dequeue; 2; enable both enqueue and dequeue
BEGIN
	DECLARE v_qman_table         VARCHAR(30) DEFAULT 'aq_sys_queue_m';
	DECLARE v_enable_value       TINYINT(1) DEFAULT 0;	

	IF p_queue_option = 0 THEN
		UPDATE aq_sys_queue_m SET ENQ_STATE = v_enable_value WHERE q_name = UPPER(p_queue_name);
	ELSEIF p_queue_option = 1 THEN
		UPDATE aq_sys_queue_m SET DEQ_STATE = v_enable_value WHERE q_name = UPPER(p_queue_name);
	ELSEIF p_queue_option = 2 THEN
		UPDATE aq_sys_queue_m SET ENQ_STATE = v_enable_value, DEQ_STATE = v_enable_value WHERE q_name = UPPER(p_queue_name);	
	END IF;	

END $$

DELIMITER ;

