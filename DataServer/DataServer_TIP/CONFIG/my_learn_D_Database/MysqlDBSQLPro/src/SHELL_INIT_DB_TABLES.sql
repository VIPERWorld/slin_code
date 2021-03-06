﻿
/**/
DELIMITER $$

DROP TABLE IF EXISTS  `ADM_SEQUENCE` $$

CREATE TABLE `ADM_SEQUENCE` (
  `SEQ_PKEY` INT NOT NULL AUTO_INCREMENT,
  `SEQ_NAME` VARCHAR(128) COLLATE utf8_bin NOT NULL,
  `INIT_NUMBER` DECIMAL(30,0) NOT NULL,
  `LAST_NUMBER` DECIMAL(30,0) NOT NULL,
  `MAX_NUMBER` DECIMAL(30,0) NOT NULL,
  `INCREMENT_BY` INT(11) NOT NULL,
  `CYCLE_FLAG` VARCHAR(1) COLLATE utf8_bin NOT NULL,
  
  PRIMARY KEY (`SEQ_PKEY`),
  UNIQUE KEY `idx_adm_seq_name` (`SEQ_NAME`) USING BTREE
  
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin $$

DELIMITER ;
/**/



/**/
DELIMITER $$

DROP TABLE IF EXISTS  `MY_LOG` $$


CREATE TABLE `MY_LOG` (
  `LOG_PKEY` DECIMAL(30,0) NOT NULL,
  `LOG_TIMESTAMP` DATETIME NOT NULL,
  `LOG_LEVEL` VARCHAR(128),
  `LOG_MSG_FUN` VARCHAR(256),
  `LOG_MSG_STR0` VARCHAR(2048),
  `LOG_MSG_STR1` VARCHAR(2048),
  `LOG_MSG_STR2` VARCHAR(2048),
  
  PRIMARY KEY (`LOG_PKEY`),
  KEY `ERRORLOG_TIMESTAMP_IDX` (`LOG_TIMESTAMP`)
  
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin $$

DELIMITER ;
/**/



/**/
DELIMITER $$

DROP TABLE IF EXISTS  `CREATE_TYPE_AS_OBJECT` $$

CREATE TABLE `CREATE_TYPE_AS_OBJECT` (
  `OBJECT_PKEY` INT NOT NULL AUTO_INCREMENT,
  `OBJECT_NAME` VARCHAR(256) COLLATE utf8_bin NOT NULL,
  `QUEUE_NAME` VARCHAR(128) COLLATE utf8_bin NOT NULL,
  `OBJECT_MSG` VARCHAR(1024) COLLATE utf8_bin NOT NULL,
  
  PRIMARY KEY (`OBJECT_PKEY`),
  UNIQUE KEY `idx_create_object_key` (`OBJECT_PKEY`) USING BTREE
  
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin $$


DELIMITER ;
/**/


/**/
DELIMITER $$

DROP TABLE IF EXISTS  `CREATE_QUEUE_RECORD` $$

CREATE TABLE `CREATE_QUEUE_RECORD` (
  `QUEUE_PKEY` INT NOT NULL AUTO_INCREMENT,
  `QUEUE_NAME` VARCHAR(128) COLLATE utf8_bin NOT NULL,
  `QUEUE_TABLE` VARCHAR(128) COLLATE utf8_bin NOT NULL,
  `QUEUE_TYPE` VARCHAR(256) COLLATE utf8_bin NOT NULL,
  `OBJECT_NAME` VARCHAR(256) COLLATE utf8_bin NOT NULL,
  `SQL_CREATE_QUEUE_TABLES` VARCHAR(2048) COLLATE utf8_bin NOT NULL,
  
  PRIMARY KEY (`QUEUE_PKEY`),
  UNIQUE KEY `idx_create_queue_key` (`QUEUE_PKEY`) USING BTREE
  
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin $$

DELIMITER ;
/**/




/**/
DELIMITER $$

DROP TABLE IF EXISTS `AQ_SAMPLE_QUEUE_NAME_T` $$

CREATE TABLE  `AQ_SAMPLE_QUEUE_NAME_T` (
  `Q_NAME` varchar(128) DEFAULT NULL,
  `MSG_SEQ_ID` bigint(30) unsigned NOT NULL,
  `MSG_UUID` varchar(64) COLLATE utf8_bin NOT NULL,
  `ENQ_TIME` DATETIME NOT NULL,
  `ENQ_UID` varchar(64) COLLATE utf8_bin DEFAULT NULL,
  `SUB_CNT` tinyint(1) unsigned DEFAULT NULL,
  `DEQ_TIME` datetime DEFAULT NULL,
  `MSG_QUALIFER` varchar(3000) COLLATE utf8_bin DEFAULT NULL,
  `ORALCE_SQL` varchar(3000) COLLATE utf8_bin DEFAULT NULL,
  `MYSQL_SQL` varchar(3000) COLLATE utf8_bin DEFAULT NULL,
  PRIMARY KEY (`MSG_UUID`),
  UNIQUE KEY `idx_qtab_msg_seq_id` (`MSG_SEQ_ID`),
  KEY `idx_qtab_enq_time` (`enq_time`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin $$


DELIMITER ;
/**/



/**/
DELIMITER $$

DROP TABLE IF EXISTS `AQ_SAMPLE_QUEUE_NAME_T_I` $$

CREATE TABLE  `AQ_SAMPLE_QUEUE_NAME_T_I` (
  `SUB_ID` int(5) unsigned NOT NULL,
  `SUB_NAME` varchar(128) COLLATE utf8_bin NOT NULL,
  `MSG_SEQ_ID` bigint(20) unsigned NOT NULL,
  `MSG_UUID` varchar(64) COLLATE utf8_bin NOT NULL,
  `ENQ_STATE` tinyint(3) unsigned NOT NULL,
  KEY `idx_sub_id` (`SUB_ID`),
  KEY `idx_sub_name` (`SUB_NAME`),
  KEY `idx_msg_sid` (`MSG_SEQ_ID`),
  KEY `idx_enq_msgid` (`MSG_UUID`),
  KEY `idx_enq_state` (`ENQ_STATE`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin $$

DELIMITER ;
/**/



/**/
DELIMITER $$

DROP TABLE IF EXISTS `AQ_SAMPLE_QUEUE_NAME_T_S` $$

CREATE TABLE  `AQ_SAMPLE_QUEUE_NAME_T_S` (
  `SUB_ID` INT(5) unsigned NOT NULL,
  `Q_NAME` VARCHAR(128) NOT NULL,
  `SUB_NAME` VARCHAR(128) DEFAULT NULL,
  `SUB_ADDRESS` VARCHAR(256) DEFAULT NULL, 
  KEY `idx_sub_id` (`SUB_ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin $$


DELIMITER ;
/**/


















