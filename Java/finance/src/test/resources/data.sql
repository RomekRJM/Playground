DROP TABLE IF EXISTS data_point;

CREATE TABLE data_point
(
    id            INT AUTO_INCREMENT PRIMARY KEY,
    date          TIME,
    advisor_name  VARCHAR(250) NOT NULL,
    currency_code VARCHAR(8)   NOT NULL,
    value         VARCHAR(64)  NOT NULL
);


DROP TABLE IF EXISTS data_point;

CREATE TABLE notification
(
    id           INT AUTO_INCREMENT PRIMARY KEY,
    date         TIME,
    advisor_name VARCHAR(250) NOT NULL,
    recipient    VARCHAR(320) NOT NULL
);