--
-- File generated with SQLiteStudio.
--
-- Text encoding used: UTF-8
--

-- Table: signalgroup
CREATE TABLE IF NOT EXISTS signalgroup (
    name TEXT CONSTRAINT PK_SGNGROUP_NAME PRIMARY KEY ON CONFLICT FAIL
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
    id           TEXT CONSTRAINT PK_SGN_ID PRIMARY KEY ON CONFLICT ROLLBACK,
    desc         TEXT NOT NULL,
    signal_group TEXT CONSTRAINT FK_SGN_SGNGRP REFERENCES signalgroup (name) 
)
STRICT;

-- Table: signalset
CREATE TABLE IF NOT EXISTS signalset (
    id        INTEGER CONSTRAINT PK_SIGNALSET PRIMARY KEY AUTOINCREMENT,
    parent_id INTEGER CONSTRAINT FK_SSET_PARENT_SSET REFERENCES signalset (id) ON DELETE CASCADE
                                                                               ON UPDATE CASCADE
);

-- Table: signalset_signal
CREATE TABLE IF NOT EXISTS signalset_signal (
    signalset_id INTEGER CONSTRAINT FK_SSET_SGN_SSET REFERENCES signalset (id) 
                         NOT NULL,
    signal_id    TEXT    CONSTRAINT FK_SSET_SGN_SGN REFERENCES signal (id) ON DELETE RESTRICT
                                                                           ON UPDATE RESTRICT
                         NOT NULL,
    idx          INTEGER NOT NULL
);

