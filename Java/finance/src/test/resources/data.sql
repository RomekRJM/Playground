DROP TABLE IF EXISTS DATA_POINT;

CREATE TABLE DATA_POINT
(
    id           INT AUTO_INCREMENT PRIMARY KEY,
    date         TIME,
    advisorName  VARCHAR(250) NOT NULL,
    currencyCode VARCHAR(8)   NOT NULL,
    value        VARCHAR(64)  NOT NULL
);