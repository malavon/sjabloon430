--
-- File generated with SQLiteStudio.
--
-- Text encoding used: UTF-8
--

-- Table: pinset
CREATE TABLE IF NOT EXISTS pinset (
    id        INTEGER PRIMARY KEY AUTOINCREMENT
                      NOT NULL,
    parent_id INTEGER REFERENCES pinset (id) ON DELETE RESTRICT
                                             ON UPDATE CASCADE,
    pins      INTEGER DEFAULT (0),
    comment   TEXT
)
STRICT;

-- Table: pinset_signalset
CREATE TABLE IF NOT EXISTS pinset_signalset (
    pinset_id   INTEGER NOT NULL
                        REFERENCES pinset (id) ON DELETE RESTRICT
                                               ON UPDATE CASCADE,
    signalset_id INTEGER NOT NULL
                         REFERENCES signalset (id) ON DELETE RESTRICT
                                                   ON UPDATE CASCADE,
    pin_bga_row  TEXT,
    pin_number   INTEGER NOT NULL,
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

