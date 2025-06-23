--
-- File generated with one of the sjabloon 430 database tools.
-- Any alterations to this data will be kept by these tools, assuming the SQL is still valid.
-- DO NOT REFORMAT THIS FILE AND CHECK IN ONLY AFTER RE-EXPORTING WITH A SJABLOON 430 TOOL.
--
-- Text encoding used: UTF-8
--
BEGIN TRANSACTION;

INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5947' , 'SLAS704', 16, 32768, 1024, 33, 2, 0, 1, 3, 16, 5, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR59471', 'SLAS704', 16, 32768, 1024, 33, 2, 0, 1, 3, 16, 5, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5948' , 'SLAS704', 16, 49152, 2048, 33, 2, 0, 1, 3, 16, 5, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5949' , 'SLAS704', 16, 65536, 2048, 33, 2, 0, 1, 3, 16, 5, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5957' , 'SLAS704', 16, 32768, 1024, 33, 2, 0, 1, 3, 16, 5, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5958' , 'SLAS704', 16, 49152, 2048, 33, 2, 0, 1, 3, 16, 5, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5959' , 'SLAS704', 16, 65536, 2048, 33, 2, 0, 1, 3, 16, 5, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5967' , 'SLAS704', 16, 32768, 1024, 40, 2, 0, 1, 3, 16, 5, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5968' , 'SLAS704', 16, 49152, 2048, 40, 2, 0, 1, 3, 16, 5, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5969' , 'SLAS704', 16, 65536, 2048, 40, 2, 0, 1, 3, 16, 5, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR59691', 'SLAS704', 16, 65536, 2048, 40, 2, 0, 1, 3, 16, 5, -40, 85, 'TI EXPORT');

INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5947' , 'ADC_SAR12', '14', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5947' , 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5947' , 'AES'      , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR59471', 'ADC_SAR12', '14', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR59471', 'BSL_I2C'  , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR59471', 'AES'      , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5948' , 'ADC_SAR12', '14', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5948' , 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5948' , 'AES'      , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5949' , 'ADC_SAR12', '14', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5949' , 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5949' , 'AES'      , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5957' , 'ADC_SAR12', '14', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5957' , 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5957' , 'AES'      , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5958' , 'ADC_SAR12', '14', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5958' , 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5958' , 'AES'      , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5959' , 'ADC_SAR12', '14', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5959' , 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5959' , 'AES'      , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5967' , 'ADC_SAR12', '16', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5967' , 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5967' , 'AES'      , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5968' , 'ADC_SAR12', '16', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5968' , 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5968' , 'AES'      , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5969' , 'ADC_SAR12', '16', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5969' , 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5969' , 'AES'      , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR59691', 'ADC_SAR12', '16', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR59691', 'BSL_I2C'  , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR59691', 'AES'      , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');

INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR59471IRHAR', 'MSP430FR59471', 'RHA', 40, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR59471IRHAT', 'MSP430FR59471', 'RHA', 40, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5947IDA'   , 'MSP430FR5947' , 'DA' , 38, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5947IDAR'  , 'MSP430FR5947' , 'DA' , 38, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5947IRHAR' , 'MSP430FR5947' , 'RHA', 40, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5947IRHAT' , 'MSP430FR5947' , 'RHA', 40, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5948IDA'   , 'MSP430FR5948' , 'DA' , 38, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5948IDAR'  , 'MSP430FR5948' , 'DA' , 38, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5948IRHAR' , 'MSP430FR5948' , 'RHA', 40, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5948IRHAT' , 'MSP430FR5948' , 'RHA', 40, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5949IDA'   , 'MSP430FR5949' , 'DA' , 38, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5949IDAR'  , 'MSP430FR5949' , 'DA' , 38, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5949IRHAR' , 'MSP430FR5949' , 'RHA', 40, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5949IRHAT' , 'MSP430FR5949' , 'RHA', 40, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5957IDA'   , 'MSP430FR5957' , 'DA' , 38, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5957IDAR'  , 'MSP430FR5957' , 'DA' , 38, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5957IRHAR' , 'MSP430FR5957' , 'RHA', 40, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5957IRHAT' , 'MSP430FR5957' , 'RHA', 40, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5958IDA'   , 'MSP430FR5958' , 'DA' , 38, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5958IDAR'  , 'MSP430FR5958' , 'DA' , 38, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5958IRHAR' , 'MSP430FR5958' , 'RHA', 40, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5958IRHAT' , 'MSP430FR5958' , 'RHA', 40, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5959IDA'   , 'MSP430FR5959' , 'DA' , 38, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5959IDAR'  , 'MSP430FR5959' , 'DA' , 38, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5959IRHAR' , 'MSP430FR5959' , 'RHA', 40, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5959IRHAT' , 'MSP430FR5959' , 'RHA', 40, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5967IRGZR' , 'MSP430FR5967' , 'RGZ', 48, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5967IRGZT' , 'MSP430FR5967' , 'RGZ', 48, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5968IRGZR' , 'MSP430FR5968' , 'RGZ', 48, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5968IRGZT' , 'MSP430FR5968' , 'RGZ', 48, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR59691IRGZR', 'MSP430FR59691', 'RGZ', 48, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR59691IRGZT', 'MSP430FR59691', 'RGZ', 48, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5969IRGZR' , 'MSP430FR5969' , 'RGZ', 48, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5969IRGZT' , 'MSP430FR5969' , 'RGZ', 48, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');

INSERT INTO pinset (id, parent_id, pins, group_idx, comment) VALUES (49, NULL, 1, 0, NULL);
INSERT INTO pinset (id, parent_id, pins, group_idx, comment) VALUES (50, NULL, 1, 0, NULL);
INSERT INTO pinset (id, parent_id, pins, group_idx, comment) VALUES (51, NULL, 1, 0, NULL);
INSERT INTO pinset (id, parent_id, pins, group_idx, comment) VALUES (52,   49, 1, 1, NULL);
INSERT INTO pinset (id, parent_id, pins, group_idx, comment) VALUES (53,   50, 1, 1, NULL);
INSERT INTO pinset (id, parent_id, pins, group_idx, comment) VALUES (54,   51, 1, 1, NULL);

INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (508, NULL, 0);
INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (509,  508, 0);

INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (49, 508, NULL, 1);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (50, 508, NULL, 5);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (51, 508, NULL, 1);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (52, 509, NULL, 1);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (53, 509, NULL, 5);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (54, 509, NULL, 1);

INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (508, 0, 'P1.0'       );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (508, 1, 'TA0.1'      );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (508, 2, 'DMAE0'      );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (509, 3, 'RTCCLK'     );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (508, 4, 'A0'         );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (508, 5, 'C0'         );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (508, 6, 'VREF-'      );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (508, 7, 'VEREF-'     );

UPDATE orderable SET pinset_id = 50 WHERE name = 'MSP430FR5957IDA'   ;
UPDATE orderable SET pinset_id = 50 WHERE name = 'MSP430FR5957IDAR'  ;
UPDATE orderable SET pinset_id = 50 WHERE name = 'MSP430FR5958IDA'   ;
UPDATE orderable SET pinset_id = 50 WHERE name = 'MSP430FR5958IDAR'  ;
UPDATE orderable SET pinset_id = 50 WHERE name = 'MSP430FR5959IDA'   ;
UPDATE orderable SET pinset_id = 50 WHERE name = 'MSP430FR5959IDAR'  ;
UPDATE orderable SET pinset_id = 53 WHERE name = 'MSP430FR5947IDA'   ;
UPDATE orderable SET pinset_id = 53 WHERE name = 'MSP430FR5947IDAR'  ;
UPDATE orderable SET pinset_id = 53 WHERE name = 'MSP430FR5948IDA'   ;
UPDATE orderable SET pinset_id = 53 WHERE name = 'MSP430FR5948IDAR'  ;
UPDATE orderable SET pinset_id = 53 WHERE name = 'MSP430FR5949IDA'   ;
UPDATE orderable SET pinset_id = 53 WHERE name = 'MSP430FR5949IDAR'  ;
UPDATE orderable SET pinset_id = 54 WHERE name = 'MSP430FR5967IRGZR' ;
UPDATE orderable SET pinset_id = 54 WHERE name = 'MSP430FR5967IRGZT' ;
UPDATE orderable SET pinset_id = 54 WHERE name = 'MSP430FR5968IRGZR' ;
UPDATE orderable SET pinset_id = 54 WHERE name = 'MSP430FR5968IRGZT' ;
UPDATE orderable SET pinset_id = 54 WHERE name = 'MSP430FR5969IRGZR' ;
UPDATE orderable SET pinset_id = 54 WHERE name = 'MSP430FR5969IRGZT' ;
UPDATE orderable SET pinset_id = 54 WHERE name = 'MSP430FR59691IRGZR';
UPDATE orderable SET pinset_id = 54 WHERE name = 'MSP430FR59691IRGZT';
UPDATE orderable SET pinset_id = 49 WHERE name = 'MSP430FR5957IRHAR' ;
UPDATE orderable SET pinset_id = 49 WHERE name = 'MSP430FR5957IRHAT' ;
UPDATE orderable SET pinset_id = 49 WHERE name = 'MSP430FR5958IRHAR' ;
UPDATE orderable SET pinset_id = 49 WHERE name = 'MSP430FR5958IRHAT' ;
UPDATE orderable SET pinset_id = 49 WHERE name = 'MSP430FR5959IRHAR' ;
UPDATE orderable SET pinset_id = 49 WHERE name = 'MSP430FR5959IRHAT' ;
UPDATE orderable SET pinset_id = 52 WHERE name = 'MSP430FR5947IRHAR' ;
UPDATE orderable SET pinset_id = 52 WHERE name = 'MSP430FR5947IRHAT' ;
UPDATE orderable SET pinset_id = 52 WHERE name = 'MSP430FR59471IRHAR';
UPDATE orderable SET pinset_id = 52 WHERE name = 'MSP430FR59471IRHAT';
UPDATE orderable SET pinset_id = 52 WHERE name = 'MSP430FR5948IRHAR' ;
UPDATE orderable SET pinset_id = 52 WHERE name = 'MSP430FR5948IRHAT' ;
UPDATE orderable SET pinset_id = 52 WHERE name = 'MSP430FR5949IRHAR' ;
UPDATE orderable SET pinset_id = 52 WHERE name = 'MSP430FR5949IRHAT' ;

COMMIT TRANSACTION;
