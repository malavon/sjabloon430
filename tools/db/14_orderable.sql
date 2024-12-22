--
-- File generated with SQLiteStudio, comment modified manually!
--
-- Text encoding used: UTF-8
--

-- Table: orderable
CREATE TABLE IF NOT EXISTS orderable (
    name       TEXT    CONSTRAINT UQ_ORDERABLE_NAME UNIQUE ON CONFLICT ROLLBACK
                       CONSTRAINT NN_ORDERABLE_NAME NOT NULL
                       PRIMARY KEY,
    package_id INTEGER CONSTRAINT NN_ORDERABLE_PACKAGE_ID NOT NULL
                       CONSTRAINT FK_ORDERABLE_PACKAGE REFERENCES package (id) ON DELETE RESTRICT,
    status     TEXT    NOT NULL,
    msl_level  INTEGER,
    comment    TEXT
)
STRICT;
