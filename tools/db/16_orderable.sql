--
-- File generated with SQLiteStudio, comment modified manually!
--
-- Text encoding used: UTF-8
--

-- Table: orderable
CREATE TABLE IF NOT EXISTS orderable (
    name        TEXT    CONSTRAINT UQ_ORDERABLE_NAME UNIQUE ON CONFLICT ROLLBACK
                        CONSTRAINT NN_ORDERABLE_NAME NOT NULL
                        PRIMARY KEY,
    device_id   INTEGER CONSTRAINT FK_ORDERABLE_DEVICE REFERENCES device (id) ON DELETE RESTRICT
                        CONSTRAINT NN_ORDERABLE_DEVICE NOT NULL,
    drawing     TEXT    CONSTRAINT NN_ODBL_DRAWING NOT NULL,
    pins        INTEGER CONSTRAINT NN_ODBL_PINS NOT NULL,
    pinset_id   INTEGER CONSTRAINT FK_ODBL_PINSET REFERENCES pinset (id) ON DELETE RESTRICT,
    status      TEXT    NOT NULL,
    msl_level   INTEGER,
    op_temp_min INTEGER,
    op_temp_max INTEGER,
    comment     TEXT,
    CONSTRAINT FK_ODBL_PACKAGE FOREIGN KEY (
        drawing,
        pins
    )
    REFERENCES package (drawing,
    pins) MATCH [FULL]
)
WITHOUT ROWID,
STRICT;
