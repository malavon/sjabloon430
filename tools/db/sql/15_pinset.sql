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

-- View: pinset_id_view
CREATE VIEW IF NOT EXISTS pinset_id_view AS
    SELECT DISTINCT datasheet_id, o.pinset_id id
    FROM orderable o
         INNER JOIN device d ON d.model = o.device_id
    UNION
    SELECT DISTINCT datasheet_id, par1.id AS id
    FROM pinset ps
         INNER JOIN pinset par1 ON ps.parent_id = par1.id
         INNER JOIN orderable o ON ps.id = o.pinset_id
         INNER JOIN device d ON d.model = o.device_id
    UNION
    SELECT DISTINCT datasheet_id, par2.id AS id
    FROM pinset ps
         INNER JOIN pinset par1 ON ps.parent_id = par1.id
         INNER JOIN pinset par2 ON par1.parent_id = par2.id
         INNER JOIN orderable o ON ps.id = o.pinset_id
         INNER JOIN device d ON d.model = o.device_id
    UNION
    SELECT DISTINCT datasheet_id, par2.parent_id AS id
    FROM pinset ps
         INNER JOIN pinset par1 ON ps.parent_id = par1.id
         INNER JOIN pinset par2 ON par1.parent_id = par2.id
         INNER JOIN orderable o ON ps.id = o.pinset_id
         INNER JOIN device d ON d.model = o.device_id
    ORDER BY datasheet_id, id ASC;
