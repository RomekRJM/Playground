DROP TABLE IF EXISTS data_point;

CREATE TABLE data_point
(
    id           INT AUTO_INCREMENT PRIMARY KEY,
    date         TIME,
    advisorName  VARCHAR(250) NOT NULL,
    currencyCode VARCHAR(8)   NOT NULL,
    value        VARCHAR(64)  NOT NULL
);