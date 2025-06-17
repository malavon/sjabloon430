--
-- File generated with one of the sjabloon 430 database tools.
-- Any alterations to this data will be kept by these tools, assuming the SQL is still valid.
-- DO NOT REFORMAT THIS FILE AND CHECK IN ONLY AFTER RE-EXPORTING WITH A SJABLOON 430 TOOL.
--
-- Text encoding used: UTF-8
--
BEGIN TRANSACTION;

INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2416', 'SLAS541', 16,  94208, 4096, 48, 2, 0, 2, 2, 8, 2, -40, 105, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2417', 'SLAS541', 16,  94208, 8192, 48, 2, 0, 2, 2, 8, 2, -40, 105, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2418', 'SLAS541', 16, 118784, 8192, 48, 2, 0, 2, 2, 8, 2, -40, 105, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2419', 'SLAS541', 16, 122880, 4096, 48, 2, 0, 2, 2, 8, 2, -40, 105, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2616', 'SLAS541', 16,  94208, 4096, 48, 2, 0, 2, 2, 8, 2, -40, 105, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2617', 'SLAS541', 16,  94208, 8192, 48, 2, 0, 2, 2, 8, 2, -40, 105, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2618', 'SLAS541', 16, 118784, 8192, 48, 2, 0, 2, 2, 8, 2, -40, 105, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2619', 'SLAS541', 16, 122880, 4096, 48, 2, 0, 2, 2, 8, 2, -40, 105, 'TI EXPORT');

INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430F2416', 'ADC_SAR12', '8' , NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430F2416', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430F2417', 'ADC_SAR12', '8' , NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430F2417', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430F2418', 'ADC_SAR12', '8' , NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430F2418', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430F2419', 'ADC_SAR12', '8' , NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430F2419', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430F2616', 'ADC_SAR12', '8' , NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430F2616', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430F2616', 'DMA'      , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430F2617', 'ADC_SAR12', '8' , NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430F2617', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430F2617', 'DMA'      , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430F2618', 'ADC_SAR12', '8' , NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430F2618', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430F2618', 'DMA'      , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430F2619', 'ADC_SAR12', '8' , NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430F2619', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430F2619', 'DMA'      , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');

INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2416TPM'  , 'MSP430F2416', 'PM' ,  64, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2416TPMR' , 'MSP430F2416', 'PM' ,  64, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2416TPN'  , 'MSP430F2416', 'PN' ,  80, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2416TPNR' , 'MSP430F2416', 'PN' ,  80, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2416TZCA' , 'MSP430F2416', 'ZCA', 113, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2416TZCAR', 'MSP430F2416', 'ZCA', 113, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2416TZQW' , 'MSP430F2416', 'ZQW', 113, 'OBSOLETE', 5,   0,   0, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2417TPM'  , 'MSP430F2417', 'PM' ,  64, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2417TPMR' , 'MSP430F2417', 'PM' ,  64, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2417TPN'  , 'MSP430F2417', 'PN' ,  80, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2417TPNR' , 'MSP430F2417', 'PN' ,  80, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2417TZCAR', 'MSP430F2417', 'ZCA', 113, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2417TZQWR', 'MSP430F2417', 'ZQW', 113, 'OBSOLETE', 5,   0,   0, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2418TPM'  , 'MSP430F2418', 'PM' ,  64, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2418TPMR' , 'MSP430F2418', 'PM' ,  64, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2418TPN'  , 'MSP430F2418', 'PN' ,  80, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2418TPNR' , 'MSP430F2418', 'PN' ,  80, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2418TZCA' , 'MSP430F2418', 'ZCA', 113, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2418TZCAR', 'MSP430F2418', 'ZCA', 113, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2419TPM'  , 'MSP430F2419', 'PM' ,  64, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2419TPMR' , 'MSP430F2419', 'PM' ,  64, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2419TPN'  , 'MSP430F2419', 'PN' ,  80, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2419TPNR' , 'MSP430F2419', 'PN' ,  80, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2419TZQWR', 'MSP430F2419', 'ZQW', 113, 'OBSOLETE', 5,   0,   0, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2616TPM'  , 'MSP430F2616', 'PM' ,  64, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2616TPMR' , 'MSP430F2616', 'PM' ,  64, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2616TPN'  , 'MSP430F2616', 'PN' ,  80, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2616TPNR' , 'MSP430F2616', 'PN' ,  80, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2616TZCA' , 'MSP430F2616', 'ZCA', 113, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2616TZCAR', 'MSP430F2616', 'ZCA', 113, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2616TZQWR', 'MSP430F2616', 'ZQW', 113, 'OBSOLETE', 5,   0,   0, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2617TPM'  , 'MSP430F2617', 'PM' ,  64, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2617TPMR' , 'MSP430F2617', 'PM' ,  64, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2617TPN'  , 'MSP430F2617', 'PN' ,  80, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2617TPNR' , 'MSP430F2617', 'PN' ,  80, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2617TZCA' , 'MSP430F2617', 'ZCA', 113, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2617TZCAR', 'MSP430F2617', 'ZCA', 113, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2617TZQW' , 'MSP430F2617', 'ZQW', 113, 'OBSOLETE', 5,   0,   0, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2617TZQWR', 'MSP430F2617', 'ZQW', 113, 'OBSOLETE', 5,   0,   0, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2618TPM'  , 'MSP430F2618', 'PM' ,  64, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2618TPMR' , 'MSP430F2618', 'PM' ,  64, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2618TPN'  , 'MSP430F2618', 'PN' ,  80, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2618TPNR' , 'MSP430F2618', 'PN' ,  80, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2618TZCA' , 'MSP430F2618', 'ZCA', 113, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2618TZCAR', 'MSP430F2618', 'ZCA', 113, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2619TPM'  , 'MSP430F2619', 'PM' ,  64, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2619TPMR' , 'MSP430F2619', 'PM' ,  64, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2619TPN'  , 'MSP430F2619', 'PN' ,  80, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2619TPNR' , 'MSP430F2619', 'PN' ,  80, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2619TZCA' , 'MSP430F2619', 'ZCA', 113, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2619TZCAR', 'MSP430F2619', 'ZCA', 113, 'ACTIVE'  , 3, -40, 105, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F2619TZQWR', 'MSP430F2619', 'ZQW', 113, 'OBSOLETE', 5,   0,   0, 'AUTOMATIC RESOLUTION');

COMMIT TRANSACTION;
