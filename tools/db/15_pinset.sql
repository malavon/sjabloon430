--
-- File generated with SQLiteStudio.
--
-- Text encoding used: UTF-8
--

-- Table: pinset
CREATE TABLE IF NOT EXISTS pinset (
    id            INTEGER CONSTRAINT PK_SET PRIMARY KEY AUTOINCREMENT,
    -- parent_set_id ANY     CONSTRAINT FK_pinset_pinset REFERENCES pinset (id) ON DELETE RESTRICT,
    pins          INTEGER NOT NULL,
    comment       TEXT
)
STRICT;

-- Table: pinset_signalset
CREATE TABLE IF NOT EXISTS pinset_signalset (
    pinset_id    INTEGER CONSTRAINT FK_PSET_SSET_PSET REFERENCES pinset (id) ON DELETE RESTRICT
                                                                             ON UPDATE RESTRICT
                         CONSTRAINT NN_PSET_SSET_PSET NOT NULL,
    signalset_id INTEGER CONSTRAINT NN_PSET_SSET_SSET NOT NULL
                         CONSTRAINT FK_PSET_SSET_SSET REFERENCES signalset (id) ON DELETE RESTRICT
                                                                                ON UPDATE RESTRICT,
    pin_bga_row  TEXT,
    pin_number   INT     NOT NULL,
    CONSTRAINT PK_PINSET_SIGNALSET PRIMARY KEY (
        pinset_id,
        signalset_id
    )
    ON CONFLICT FAIL,
    CONSTRAINT UQ_SIGNAL_SET_PK UNIQUE (
        pinset_id,
        signalset_id
    )
    ON CONFLICT FAIL
)
WITHOUT ROWID,
STRICT;
