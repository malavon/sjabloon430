--
-- File generated with SQLiteStudio v3.4.4
--
-- Text encoding used: UTF-8
--
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- Table: datasheet
CREATE TABLE IF NOT EXISTS datasheet (
    id          TEXT    PRIMARY KEY ON CONFLICT ROLLBACK,
    revision    TEXT,
    issue_month INTEGER NOT NULL,
    issue_year  INTEGER NOT NULL,
    rev_month   INTEGER NOT NULL,
    rev_year    INTEGER NOT NULL,
    comment     TEXT
)
WITHOUT ROWID,
STRICT;

INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS241', 'I', 9, 1999, 12, 2008, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS256', 'D', 11, 1999, 9, 2004, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS272', 'H', 7, 2000, 5, 2018, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS312', 'C', 7, 2001, 9, 2004, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS340', 'J', 5, 2001, 12, 2008, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS344', 'G', 1, 2002, 10, 2009, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS361', 'D', 1, 2002, 8, 2004, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS368', 'G', 10, 2002, 3, 2011, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS380', 'F', 4, 2004, 3, 2022, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS383', 'E', 10, 2003, 12, 2013, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS396', 'D', 7, 2003, 11, 2016, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS439', 'F', 9, 2004, 8, 2011, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS491', 'I', 8, 2005, 12, 2012, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS504', 'G', 7, 2006, 8, 2012, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS508', 'K', 4, 2006, 5, 2020, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS518', 'E', 8, 2006, 8, 2011, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS541', 'M', 6, 2007, 3, 2022, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS545', 'C', 5, 2007, 3, 2011, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS547', 'I', 6, 2007, 12, 2012, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS554', 'I', 5, 2009, 9, 2018, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS555', 'B', 6, 2012, 9, 2018, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS556', 'A', 7, 2007, 8, 2007, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS566', 'G', 6, 2010, 9, 2020, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS578', 'J', 11, 2007, 1, 2012, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS580', 'E', 10, 2008, 5, 2020, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS587', '', 2, 2008, 2, 2008, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS588', '', 2, 2008, 2, 2008, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS590', 'P', 3, 2009, 9, 2020, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS614', 'D', 9, 2008, 5, 2011, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS616', '', 7, 2008, 7, 2008, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS619', 'R', 8, 2010, 9, 2018, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS626', 'C', 10, 2008, 3, 2011, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS629', 'B', 3, 2009, 5, 2020, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS639', 'L', 7, 2011, 12, 2017, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS648', 'E', 4, 2009, 3, 2011, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS650', 'G', 5, 2010, 9, 2020, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS655', 'H', 1, 2010, 5, 2021, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS673', '', 9, 2010, 9, 2010, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS677', 'G', 9, 2010, 5, 2020, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS678', 'G', 8, 2010, 9, 2020, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS694', 'J', 2, 2010, 2, 2013, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS695', 'I', 2, 2010, 2, 2013, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS697', 'E', 3, 2010, 11, 2016, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS700', 'E', 10, 2012, 9, 2020, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS701', 'B', 11, 2010, 6, 2018, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS703', 'C', 4, 2010, 9, 2020, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS704', 'G', 10, 2012, 8, 2018, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS706', 'F', 7, 2011, 9, 2018, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS713', '', 6, 2010, 6, 2010, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS718', 'H', 11, 2012, 9, 2018, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS720', 'F', 8, 2010, 9, 2020, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS721', 'F', 8, 2010, 9, 2020, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS722', 'G', 12, 2010, 5, 2013, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS723', 'H', 12, 2010, 5, 2013, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS731', 'D', 12, 2011, 9, 2018, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS734', 'G', 4, 2011, 4, 2016, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS735', 'J', 4, 2011, 5, 2013, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS753', 'E', 1, 2012, 2, 2013, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS768', 'E', 9, 2012, 9, 2018, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS770', 'B', 11, 2011, 3, 2014, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS774', 'A', 7, 2011, 10, 2011, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS775', 'E', 8, 2011, 3, 2014, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS787', 'B', 11, 2011, 3, 2014, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS789', 'D', 6, 2014, 8, 2018, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS797', 'C', 8, 2014, 8, 2018, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS800', '', 3, 2013, 3, 2013, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS815', 'D', 11, 2012, 9, 2018, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS824', '', 12, 2013, 12, 2013, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS862', '', 6, 2012, 6, 2012, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS863', '', 8, 2012, 8, 2012, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS865', 'F', 10, 2014, 12, 2021, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS868', 'A', 6, 2012, 11, 2012, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS874', 'B', 5, 2015, 9, 2020, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS885', 'A', 8, 2012, 10, 2012, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS887', 'C', 9, 2014, 3, 2021, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS892', 'C', 3, 2013, 9, 2014, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS897', 'C', 9, 2013, 10, 2020, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS903', 'D', 5, 2013, 10, 2020, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS913', 'A', 7, 2013, 8, 2013, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS942', 'E', 11, 2015, 12, 2019, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS954', '', 12, 2013, 12, 2013, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS966', '', 3, 2014, 3, 2014, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS967', 'A', 1, 2014, 1, 2014, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS982', 'A', 5, 2014, 9, 2018, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS983', 'A', 5, 2014, 9, 2018, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLAS998', 'A', 6, 2014, 10, 2018, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLASE23', 'E', 1, 2015, 8, 2018, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLASE32', 'C', 8, 2014, 8, 2018, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLASE33', 'C', 8, 2014, 8, 2018, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLASE34', 'E', 5, 2014, 8, 2018, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLASE35', 'C', 5, 2014, 12, 2017, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLASE45', 'E', 10, 2014, 12, 2019, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLASE46', 'A', 2, 2015, 10, 2018, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLASE50', 'A', 2, 2015, 10, 2018, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLASE54', 'D', 3, 2016, 1, 2021, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLASE58', 'E', 2, 2016, 12, 2019, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLASE59', 'F', 10, 2015, 12, 2019, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLASE66', 'C', 4, 2015, 8, 2018, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLASE78', 'E', 8, 2016, 6, 2021, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLASEB7', 'D', 6, 2017, 12, 2020, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLASEC3', 'A', 8, 2016, 8, 2016, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLASEC4', 'D', 5, 2018, 12, 2019, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLASEC9', '', 4, 2017, 4, 2017, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLASEE4', 'C', 1, 2018, 12, 2019, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLASEE5', 'D', 1, 2018, 1, 2021, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLASEF5', 'B', 1, 2019, 12, 2021, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLASEK0', 'A', 12, 2017, 3, 2018, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLASEO5', 'D', 3, 2019, 9, 2021, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLASEO7', 'C', 3, 2019, 9, 2021, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLASEU5', 'A', 10, 2019, 2, 2021, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLASEV3', 'A', 3, 2020, 12, 2020, NULL);
INSERT INTO datasheet (id, revision, issue_month, issue_year, rev_month, rev_year, comment) VALUES ('SLVSCN6', 'A', 11, 2014, 12, 2014, NULL);


-- Table: device
CREATE TABLE IF NOT EXISTS device (
    id            INTEGER PRIMARY KEY ON CONFLICT ROLLBACK AUTOINCREMENT
                          NOT NULL,
    datasheet_id  TEXT    REFERENCES datasheet (id) ON DELETE RESTRICT
                          NOT NULL,
    model         TEXT    NOT NULL
                          UNIQUE,
    freq_max      INTEGER,
    storage_bytes INTEGER,
    ram_bytes     INTEGER,
    gpio_count    INTEGER,
    uart_count    INTEGER,
    usb_count     INTEGER DEFAULT (0),
    i2c_count     INTEGER,
    spi_count     INTEGER,
    comp_count    INTEGER,
    timer_count   INTEGER,
    op_temp_min   INTEGER,
    op_temp_max   INTEGER,
    comment       TEXT
)
STRICT;


-- Table: device_feature
CREATE TABLE IF NOT EXISTS device_feature (
    device_id  INTEGER REFERENCES device (id) ON DELETE RESTRICT
                       NOT NULL,
    feature_id TEXT    REFERENCES feature (id) ON DELETE RESTRICT
                       NOT NULL,
    param1     ANY,
    param2     ANY,
    param3     ANY,
    comment    TEXT
)
STRICT;


-- Table: feature
CREATE TABLE IF NOT EXISTS feature (
    id                 TEXT PRIMARY KEY,
    param1_description TEXT,
    param2_description ANY,
    param3_description ANY,
    comment            TEXT,
    family_text        TEXT,
    family_group       TEXT
)
WITHOUT ROWID,
STRICT;

INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('ADC_SAR10', 'External channels', 'Internal channels', NULL, '10-bit SAR ADC', '10-bit SAR', 'ADC');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('ADC_SAR12', 'External channels', 'Internal channels', NULL, '12-bit SAR ADC', '12-bit SAR', 'ADC');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('ADC_SD16', 'External channels', 'Internal channels', NULL, '16-bit Sigma Delta ADC', '16-bit Sigma Delta', 'ADC');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('ADC_SD24', 'External channels', 'Internal channels', NULL, '24-bit Sigma Delta ADC', '24-bit Sigma Delta', 'ADC');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('ADC_SLOPE', NULL, NULL, NULL, 'Slope ADC', 'Slope', 'ADC');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('ADV_SENSE', NULL, NULL, NULL, 'Included in TI export as feature', 'Advanced sensing', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('AES', NULL, NULL, NULL, 'AES Encryption/Decryption', 'AES', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('AFE', 'TODO', NULL, NULL, '??', 'Ultrasonic sensing AFE', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('BOD', NULL, NULL, NULL, 'Brownout Detect', 'Brown out detector', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('BOR', NULL, NULL, NULL, 'Brownout Reset', 'Brown out reset', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('BSL_I2C', NULL, NULL, NULL, 'Bootloader I²C version', 'I2C', 'BSL');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('BSL_UART', NULL, NULL, NULL, 'Bootloader UART version', 'UART', 'BSL');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('BSL_USB', NULL, NULL, NULL, 'Bootlloader USB version', 'USB', 'BSL');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('DIRECT', NULL, NULL, NULL, 'Included in TI export as feature', 'Direct drive', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('DMA', NULL, NULL, NULL, 'Direct Memory Access', 'DMA', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('HW_MUL32', NULL, NULL, NULL, NULL, '32-bit hardware multiplier', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('IGNORE_5V_IOS', NULL, NULL, NULL, 'Included in TI export as feature', '5-V-tolerant I/Os', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('IGNORE_BSL', NULL, NULL, NULL, 'Included in TI export as feature', 'Bootstrap loader', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('IGNORE_SD', '? not certain ignore', NULL, NULL, 'Included in TI export as feature', 'Sigma delta', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('IO_1.8V', NULL, NULL, NULL, NULL, '1.8V I/O', 'Special I/O');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('IO_5.0V_TOL', NULL, NULL, NULL, NULL, '5V Tolerant I/O', 'Special I/O');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('IO_CAPTIVATE', NULL, NULL, NULL, NULL, 'CapTIvate Touch I/O', 'Special I/O');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('IRML', 'TODO? part of USCI too?', NULL, NULL, '??', 'IR Modulation Logic', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('LCD', 'Type (A-E)', '# Common', '# Elements', 'LCD ontroller', 'LCD', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('LEA', NULL, NULL, NULL, '??', 'Low-energy accelerator (LEA)', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('MTIF', NULL, NULL, NULL, '??', 'Metering test interface (MTIF)', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('OP_AMP', NULL, NULL, NULL, '??', 'OpAmp', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('PGA', NULL, NULL, NULL, '??', 'PGA', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('RTC', NULL, NULL, NULL, 'Real-time clock', NULL, 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('SAC_DAC', NULL, NULL, NULL, 'SAC DAC?', 'DAC', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('SCAN', NULL, NULL, NULL, '??', 'Scan interface', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('SPY_WIRE', NULL, NULL, NULL, '??', 'Spy-bi-wire', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('TEMP_SENSOR', NULL, NULL, NULL, 'Temperature Sensor', 'Temp sensor', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('TRANS_AMP', 'TODO', NULL, NULL, '??', 'Transimpedance amplifier', 'Features');
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('USCI_A', 'TODO: not all IrDA? all LIn?', NULL, NULL, 'USCI with IrDA, UART, SPI', NULL, NULL);
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('USCI_A_LIN', 'TODO: not all IrDA?', NULL, NULL, 'USCI with IrDA, UART, SPI', NULL, NULL);
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('USCI_B', NULL, NULL, NULL, 'USCI with I²C, SPI', NULL, NULL);
INSERT INTO feature (id, param1_description, param2_description, param3_description, comment, family_text, family_group) VALUES ('WTD+', NULL, NULL, NULL, NULL, 'Watchdog timer', 'Features');

COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
