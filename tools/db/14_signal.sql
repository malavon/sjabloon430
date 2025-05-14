--
-- File generated with SQLiteStudio.
--
-- Text encoding used: UTF-8
--

-- Table: signalgroup
CREATE TABLE IF NOT EXISTS signalgroup (
    name TEXT CONSTRAINT PK_SIGNALGROUP_NAME PRIMARY KEY
            CONSTRAINT UQ_SIGNALGROUP_NAME UNIQUE
);

BEGIN TRANSACTION;

INSERT INTO signalgroup (name) VALUES ('ADC_SAR');
INSERT INTO signalgroup (name) VALUES ('ADC_SD');
INSERT INTO signalgroup (name) VALUES ('BSL');
INSERT INTO signalgroup (name) VALUES ('DMA');
INSERT INTO signalgroup (name) VALUES ('CAPTIVATE');
INSERT INTO signalgroup (name) VALUES ('LCD');
INSERT INTO signalgroup (name) VALUES ('USCI_A');
INSERT INTO signalgroup (name) VALUES ('USCI_B');

COMMIT TRANSACTION;

-- Table: signal
CREATE TABLE IF NOT EXISTS signal (
    id      TEXT PRIMARY KEY ON CONFLICT ROLLBACK
                 NOT NULL,
    desc    TEXT NOT NULL,
    signal_group TEXT CONSTRAINT FK_SIGNAL_GROUP REFERENCES signalgroup (name) 
)
STRICT;
