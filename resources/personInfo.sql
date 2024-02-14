DROP TABLE IF EXISTS `t_auth`;
CREATE TABLE `t_auth` (
  `id` int NOT NULL AUTO_INCREMENT,
  `person_id` int DEFAULT NULL,
  `auth` varchar(255) COLLATE utf8mb4_general_ci DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `person_id` (`person_id`),
  CONSTRAINT `t_auth_ibfk_1` FOREIGN KEY (`person_id`) REFERENCES `t_person` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
BEGIN;
INSERT INTO `t_auth` VALUES (1, 1, '普通用户');
INSERT INTO `t_auth` VALUES (2, 2, '普通用户');
INSERT INTO `t_auth` VALUES (3, 3, '普通用户');
INSERT INTO `t_auth` VALUES (4, 4, '普通用户');
INSERT INTO `t_auth` VALUES (5, 5, '管理员');
INSERT INTO `t_auth` VALUES (6, 6, '普通用户');
INSERT INTO `t_auth` VALUES (7, 7, '普通用户');
COMMIT;
DROP TABLE IF EXISTS `t_department`;
CREATE TABLE `t_department` (
  `id` int NOT NULL AUTO_INCREMENT,
  `department_id` int DEFAULT NULL,
  `department_name` varchar(255) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `manager_id` int DEFAULT NULL,
  `department_status` int DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
BEGIN;
INSERT INTO `t_department` VALUES (1, 0, '前端', NULL, NULL);
INSERT INTO `t_department` VALUES (2, 1, '后端', NULL, NULL);
INSERT INTO `t_department` VALUES (3, 2, '产品', NULL, NULL);
INSERT INTO `t_department` VALUES (4, 3, '综管', NULL, NULL);
INSERT INTO `t_department` VALUES (5, 4, '测试', NULL, NULL);
COMMIT;
DROP TABLE IF EXISTS `t_level`;
CREATE TABLE `t_level` (
  `id` int NOT NULL AUTO_INCREMENT,
  `level_id` int DEFAULT NULL,
  `level_name` varchar(255) COLLATE utf8mb4_general_ci DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
BEGIN;
INSERT INTO `t_level` VALUES (1, 0, '初级');
INSERT INTO `t_level` VALUES (2, 1, '中级');
INSERT INTO `t_level` VALUES (3, 2, '高级');
INSERT INTO `t_level` VALUES (4, 3, '专家');
COMMIT;
DROP TABLE IF EXISTS `t_location`;
CREATE TABLE `t_location` (
  `id` int NOT NULL AUTO_INCREMENT,
  `person_id` int DEFAULT NULL,
  `longitude` double DEFAULT NULL,
  `latitude` double DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `person_id` (`person_id`),
  CONSTRAINT `t_location_ibfk_1` FOREIGN KEY (`person_id`) REFERENCES `t_person` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
BEGIN;
INSERT INTO `t_location` VALUES (1, 1, 124, 35.4);
INSERT INTO `t_location` VALUES (2, 2, 99.3, 20.6);
INSERT INTO `t_location` VALUES (3, 3, 110.5, 43.9);
INSERT INTO `t_location` VALUES (4, 4, 100.2, 30.4);
INSERT INTO `t_location` VALUES (5, 5, 122.3, 25.6);
INSERT INTO `t_location` VALUES (6, 6, 135.05, 48.27);
COMMIT;
DROP TABLE IF EXISTS `t_office`;
CREATE TABLE `t_office` (
  `id` int NOT NULL AUTO_INCREMENT,
  `office_id` int DEFAULT NULL,
  `office_name` varchar(255) COLLATE utf8mb4_general_ci DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
BEGIN;
INSERT INTO `t_office` VALUES (1, 0, '员工');
INSERT INTO `t_office` VALUES (2, 1, '经理');
INSERT INTO `t_office` VALUES (3, 2, 'CEO');
INSERT INTO `t_office` VALUES (4, 3, '董事长');
COMMIT;
DROP TABLE IF EXISTS `t_person`;
CREATE TABLE `t_person` (
  `id` int NOT NULL AUTO_INCREMENT,
  `number` varchar(255) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `level` int DEFAULT NULL,
  `name` varchar(255) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `born` date DEFAULT NULL,
  `tel` varchar(255) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `office` int DEFAULT NULL,
  `department` int DEFAULT NULL,
  `intime` datetime DEFAULT NULL,
  `property` varchar(255) COLLATE utf8mb4_general_ci DEFAULT NULL,
  `leave_s` int DEFAULT NULL,
  `away_s` int DEFAULT NULL,
  `admin` int DEFAULT NULL,
  `delete_s` int DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `level` (`level`),
  KEY `office` (`office`),
  CONSTRAINT `t_person_ibfk_1` FOREIGN KEY (`level`) REFERENCES `t_level` (`id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `t_person_ibfk_2` FOREIGN KEY (`office`) REFERENCES `t_office` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;
BEGIN;
INSERT INTO `t_person` VALUES (1, '123', 1, '小强', '1994-01-01', '12345678901', 1, 1, '2022-05-01 00:00:00', '正常', 0, 0, 0, 0);
INSERT INTO `t_person` VALUES (2, '124', 2, '小红', '1998-12-31', '12345678901', 1, 0, '2022-05-31 15:02:18', '正常', 0, 0, 0, 0);
INSERT INTO `t_person` VALUES (3, '125', 2, '小明', '1995-01-01', '13335330356', 1, 2, '2020-10-01 00:00:00', '正常', 0, 0, 0, 0);
INSERT INTO `t_person` VALUES (4, '126', 2, '小李', '1997-09-10', '12345678901', 1, 3, '2021-09-10 00:00:00', '正常', 0, 0, 0, 0);
INSERT INTO `t_person` VALUES (5, '127', 2, '小王', '1999-01-01', '15678941234', 1, 2, '2021-10-31 00:00:00', '正常', 0, 0, 1, 0);
INSERT INTO `t_person` VALUES (6, '128', 1, '小紫', '1995-01-02', '12345678901', 1, 0, '2022-06-01 00:00:00', '正常', 0, 0, 0, 0);
INSERT INTO `t_person` VALUES (7, '129', 1, '小亮', '1990-01-31', '12345678901', 1, 1, '2021-01-01 00:00:00', '外援', 0, 0, 0, 0);
COMMIT;
