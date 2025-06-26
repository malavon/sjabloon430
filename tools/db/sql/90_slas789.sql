--
-- File generated with one of the sjabloon 430 database tools.
-- Any alterations to this data will be kept by these tools, assuming the SQL is still valid.
-- DO NOT REFORMAT THIS FILE AND CHECK IN ONLY AFTER RE-EXPORTING WITH A SJABLOON 430 TOOL.
--
-- Text encoding used: UTF-8
--
BEGIN TRANSACTION;

INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5986' , 'SLAS789', 16,  49152, 2048, 48, 2, 0, 2, 4, 12, 5, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5987' , 'SLAS789', 16,  65536, 2048, 48, 2, 0, 2, 4, 12, 5, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5988' , 'SLAS789', 16,  98304, 2048, 48, 2, 0, 2, 4, 12, 5, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5989' , 'SLAS789', 16, 131072, 2048, 48, 2, 0, 2, 4, 12, 5, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR59891', 'SLAS789', 16, 131072, 2048, 48, 2, 0, 2, 4, 12, 5, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR6987' , 'SLAS789', 16,  65536, 2048, 83, 2, 0, 2, 4, 16, 5, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR6988' , 'SLAS789', 16,  98304, 2048, 83, 2, 0, 2, 4, 16, 5, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR6989' , 'SLAS789', 16, 131072, 2048, 83, 2, 0, 2, 4, 16, 5, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR69891', 'SLAS789', 16, 131072, 2048, 83, 2, 0, 2, 4, 16, 5, -40, 85, 'TI EXPORT');

INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5986' , 'ADC_SAR12', '12', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5986' , 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5986' , 'ADV_SENSE', NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5987' , 'ADC_SAR12', '12', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5987' , 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5987' , 'ADV_SENSE', NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5988' , 'ADC_SAR12', '12', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5988' , 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5988' , 'ADV_SENSE', NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5989' , 'ADC_SAR12', '12', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5989' , 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR5989' , 'ADV_SENSE', NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR59891', 'ADC_SAR12', '12', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR59891', 'BSL_I2C'  , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR59891', 'ADV_SENSE', NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR6987' , 'ADC_SAR12', '16', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR6987' , 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR6987' , 'ADV_SENSE', NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR6988' , 'ADC_SAR12', '16', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR6988' , 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR6988' , 'ADV_SENSE', NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR6989' , 'ADC_SAR12', '16', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR6989' , 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR6989' , 'ADV_SENSE', NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR69891', 'ADC_SAR12', '16', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR69891', 'BSL_I2C'  , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR69891', 'ADV_SENSE', NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');

INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5986IPM'   , 'MSP430FR5986' , 'PM' ,  64, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5986IPMR'  , 'MSP430FR5986' , 'PM' ,  64, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5987IPM'   , 'MSP430FR5987' , 'PM' ,  64, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5987IPMR'  , 'MSP430FR5987' , 'PM' ,  64, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5987IRGCR' , 'MSP430FR5987' , 'RGC',  64, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5987IRGCT' , 'MSP430FR5987' , 'RGC',  64, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5988IPM'   , 'MSP430FR5988' , 'PM' ,  64, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5988IRGCT' , 'MSP430FR5988' , 'RGC',  64, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR59891IPM'  , 'MSP430FR59891', 'PM' ,  64, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR59891IRGCT', 'MSP430FR59891', 'RGC',  64, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5989IPM'   , 'MSP430FR5989' , 'PM' ,  64, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5989IPMR'  , 'MSP430FR5989' , 'PM' ,  64, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5989IRGCR' , 'MSP430FR5989' , 'RGC',  64, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR5989IRGCT' , 'MSP430FR5989' , 'RGC',  64, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR6987IPN'   , 'MSP430FR6987' , 'PN' ,  80, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR6987IPNR'  , 'MSP430FR6987' , 'PN' ,  80, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR6987IPZ'   , 'MSP430FR6987' , 'PZ' , 100, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR6988IPN'   , 'MSP430FR6988' , 'PN' ,  80, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR6988IPNR'  , 'MSP430FR6988' , 'PN' ,  80, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR6988IPZ'   , 'MSP430FR6988' , 'PZ' , 100, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR69891IPN'  , 'MSP430FR69891', 'PN' ,  80, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR69891IPZ'  , 'MSP430FR69891', 'PZ' , 100, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR69891IPZR' , 'MSP430FR69891', 'PZ' , 100, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR6989IPN'   , 'MSP430FR6989' , 'PN' ,  80, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR6989IPNR'  , 'MSP430FR6989' , 'PN' ,  80, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR6989IPZ'   , 'MSP430FR6989' , 'PZ' , 100, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR6989IPZR'  , 'MSP430FR6989' , 'PZ' , 100, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');

INSERT INTO pinset (id, parent_id, pins, group_idx, comment) VALUES (70, NULL, 0, 0, NULL);
INSERT INTO pinset (id, parent_id, pins, group_idx, comment) VALUES (71, NULL, 0, 0, NULL);
INSERT INTO pinset (id, parent_id, pins, group_idx, comment) VALUES (72, NULL, 2, 0, NULL);
INSERT INTO pinset (id, parent_id, pins, group_idx, comment) VALUES (73, NULL, 2, 0, NULL);
INSERT INTO pinset (id, parent_id, pins, group_idx, comment) VALUES (74,   72, 0, 1, NULL);
INSERT INTO pinset (id, parent_id, pins, group_idx, comment) VALUES (75,   73, 0, 1, NULL);
INSERT INTO pinset (id, parent_id, pins, group_idx, comment) VALUES (76,   75, 1, 2, NULL);
INSERT INTO pinset (id, parent_id, pins, group_idx, comment) VALUES (77,   74, 1, 3, NULL);

INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (752, NULL, 0);
INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (753, NULL, 1);
INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (754,  753, 1);
INSERT INTO signalset (id, parent_id, datasheet_idx) VALUES (755,  754, 1);

INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (72, 752, NULL, 1);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (73, 752, NULL, 1);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (72, 753, NULL, 2);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (73, 753, NULL, 2);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (76, 754, NULL, 2);
INSERT INTO pinset_signalset (pinset_id, signalset_id, pin_bga_row, pin_number) VALUES (77, 755, NULL, 2);

INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (752, 0, 'P4.3'       );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (752, 1, 'UCA0SOMI'   );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (752, 2, 'UCA0RXD'    );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (752, 3, 'UCB1STE'    );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (753, 0, 'P1.4'       );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (753, 1, 'UCB0CLK'    );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (753, 2, 'UCA0STE'    );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (753, 3, 'TA1.0'      );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (754, 4, 'S1'         );
INSERT INTO signalset_signal (signalset_id, idx, signal_id) VALUES (755, 5, 'S3'         );

UPDATE orderable SET pinset_id = 70 WHERE name = 'MSP430FR5986IPM'   ;
UPDATE orderable SET pinset_id = 70 WHERE name = 'MSP430FR5986IPMR'  ;
UPDATE orderable SET pinset_id = 70 WHERE name = 'MSP430FR5987IPM'   ;
UPDATE orderable SET pinset_id = 70 WHERE name = 'MSP430FR5987IPMR'  ;
UPDATE orderable SET pinset_id = 70 WHERE name = 'MSP430FR5988IPM'   ;
UPDATE orderable SET pinset_id = 70 WHERE name = 'MSP430FR5989IPM'   ;
UPDATE orderable SET pinset_id = 70 WHERE name = 'MSP430FR5989IPMR'  ;
UPDATE orderable SET pinset_id = 70 WHERE name = 'MSP430FR59891IPM'  ;
UPDATE orderable SET pinset_id = 77 WHERE name = 'MSP430FR6987IPN'   ;
UPDATE orderable SET pinset_id = 77 WHERE name = 'MSP430FR6987IPNR'  ;
UPDATE orderable SET pinset_id = 77 WHERE name = 'MSP430FR6988IPN'   ;
UPDATE orderable SET pinset_id = 77 WHERE name = 'MSP430FR6988IPNR'  ;
UPDATE orderable SET pinset_id = 77 WHERE name = 'MSP430FR6989IPN'   ;
UPDATE orderable SET pinset_id = 77 WHERE name = 'MSP430FR6989IPNR'  ;
UPDATE orderable SET pinset_id = 77 WHERE name = 'MSP430FR69891IPN'  ;
UPDATE orderable SET pinset_id = 76 WHERE name = 'MSP430FR6987IPZ'   ;
UPDATE orderable SET pinset_id = 76 WHERE name = 'MSP430FR6988IPZ'   ;
UPDATE orderable SET pinset_id = 76 WHERE name = 'MSP430FR6989IPZ'   ;
UPDATE orderable SET pinset_id = 76 WHERE name = 'MSP430FR6989IPZR'  ;
UPDATE orderable SET pinset_id = 76 WHERE name = 'MSP430FR69891IPZ'  ;
UPDATE orderable SET pinset_id = 76 WHERE name = 'MSP430FR69891IPZR' ;
UPDATE orderable SET pinset_id = 71 WHERE name = 'MSP430FR5987IRGCR' ;
UPDATE orderable SET pinset_id = 71 WHERE name = 'MSP430FR5987IRGCT' ;
UPDATE orderable SET pinset_id = 71 WHERE name = 'MSP430FR5988IRGCT' ;
UPDATE orderable SET pinset_id = 71 WHERE name = 'MSP430FR5989IRGCR' ;
UPDATE orderable SET pinset_id = 71 WHERE name = 'MSP430FR5989IRGCT' ;
UPDATE orderable SET pinset_id = 71 WHERE name = 'MSP430FR59891IRGCT';

COMMIT TRANSACTION;
