--
-- File generated with SQLiteStudio.
--
-- Text encoding used: UTF-8
--

-- Table: orderable
CREATE TABLE IF NOT EXISTS orderable (
    name       TEXT    UNIQUE ON CONFLICT ROLLBACK
                       NOT NULL
                       PRIMARY KEY,
    package_id INTEGER NOT NULL
                       REFERENCES package (id) ON DELETE RESTRICT,
    status     TEXT    NOT NULL,
    msl_level  INTEGER,
    comment    TEXT
)
STRICT;
