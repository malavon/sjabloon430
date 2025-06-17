--
-- File generated with one of the sjabloon 430 database tools.
-- Any alterations to this data will be kept by these tools, assuming the SQL is still valid.
-- DO NOT REFORMAT THIS FILE AND CHECK IN ONLY AFTER RE-EXPORTING WITH A SJABLOON 430 TOOL.
--
-- Text encoding used: UTF-8
--
BEGIN TRANSACTION;

INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2153', 'SLASEC4', 24, 16384, 2048, 44, 2, 0, 2, 4, 2, 4, -40, 105, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2155', 'SLASEC4', 24, 32768, 4096, 44, 2, 0, 2, 4, 2, 4, -40, 105, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2353', 'SLASEC4', 24, 16384, 2048, 44, 2, 0, 2, 4, 2, 4, -40, 105, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2355', 'SLASEC4', 24, 32768, 4096, 44, 2, 0, 2, 4, 2, 4, -40, 105, 'TI EXPORT');

INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR2153', 'ADC_SAR12', '12', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR2153', 'BSL_I2C', NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR2155', 'ADC_SAR12', '12', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR2155', 'BSL_I2C', NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR2353', 'ADC_SAR12', '12', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR2353', 'BSL_I2C', NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR2353', 'SAC_DAC', NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR2355', 'ADC_SAR12', '12', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR2355', 'BSL_I2C', NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR2355', 'SAC_DAC', NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');

INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2153TDBT'  , 'MSP430FR2153', 'DBT',  38, 'ACTIVE', 2, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2153TDBTR' , 'MSP430FR2153', 'DBT',  38, 'ACTIVE', 2, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2153TPT'   , 'MSP430FR2153', 'PT' ,  48, 'ACTIVE', 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2153TPTR'  , 'MSP430FR2153', 'PT' ,  48, 'ACTIVE', 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2153TRHAR' , 'MSP430FR2153', 'RHA',  40, 'ACTIVE', 1, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2153TRHAT' , 'MSP430FR2153', 'RHA',  40, 'ACTIVE', 1, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2153TRSMR' , 'MSP430FR2153', 'RSM',  32, 'ACTIVE', 1, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2153TRSMT' , 'MSP430FR2153', 'RSM',  32, 'ACTIVE', 1, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2155TDBT'  , 'MSP430FR2155', 'DBT',  38, 'ACTIVE', 2, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2155TDBTR' , 'MSP430FR2155', 'DBT',  38, 'ACTIVE', 2, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2155TPT'   , 'MSP430FR2155', 'PT' ,  48, 'ACTIVE', 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2155TPTR'  , 'MSP430FR2155', 'PT' ,  48, 'ACTIVE', 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2155TRHAR' , 'MSP430FR2155', 'RHA',  40, 'ACTIVE', 1, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2155TRHAT' , 'MSP430FR2155', 'RHA',  40, 'ACTIVE', 1, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2155TRSMR' , 'MSP430FR2155', 'RSM',  32, 'ACTIVE', 1, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2155TRSMT' , 'MSP430FR2155', 'RSM',  32, 'ACTIVE', 1, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2353TDBT'  , 'MSP430FR2353', 'DBT',  38, 'ACTIVE', 2, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2353TDBTR' , 'MSP430FR2353', 'DBT',  38, 'ACTIVE', 2, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2353TPT'   , 'MSP430FR2353', 'PT' ,  48, 'ACTIVE', 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2353TPTR'  , 'MSP430FR2353', 'PT' ,  48, 'ACTIVE', 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2353TRHAR' , 'MSP430FR2353', 'RHA',  40, 'ACTIVE', 1, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2353TRHAT' , 'MSP430FR2353', 'RHA',  40, 'ACTIVE', 1, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2353TRSMR' , 'MSP430FR2353', 'RSM',  32, 'ACTIVE', 1, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2353TRSMT' , 'MSP430FR2353', 'RSM',  32, 'ACTIVE', 1, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2355TDBT'  , 'MSP430FR2355', 'DBT',  38, 'ACTIVE', 2, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2355TDBTR' , 'MSP430FR2355', 'DBT',  38, 'ACTIVE', 2, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2355TPT'   , 'MSP430FR2355', 'PT' ,  48, 'ACTIVE', 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2355TPTR'  , 'MSP430FR2355', 'PT' ,  48, 'ACTIVE', 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2355TRHAR' , 'MSP430FR2355', 'RHA',  40, 'ACTIVE', 1, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2355TRHAT' , 'MSP430FR2355', 'RHA',  40, 'ACTIVE', 1, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2355TRSMR' , 'MSP430FR2355', 'RSM',  32, 'ACTIVE', 1, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2355TRSMT' , 'MSP430FR2355', 'RSM',  32, 'ACTIVE', 1, -40, 105, 'AUTOMATIC RESOLUTION');

COMMIT TRANSACTION;
