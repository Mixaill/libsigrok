/*
 * This file is part of the libsigrok project.
 *
 * Copyright (C) 2020 Mikhail Paulyshka <paulyshka@bsu.by>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <config.h>
#include "protocol.h"

#include "libauris_device_b480_api.h"

static struct sr_dev_driver auris_b480_driver_info;

static const uint32_t scanopts[] = {
};

static const uint32_t drvopts[] = {
	SR_CONF_OSCILLOSCOPE
};

static const uint32_t devopts[] = {
};


static const char *channel_names[] = {
	"CH1", "CH2", "CH3", "CH4", 
	"CH5", "CH6", "CH7", "CH8"
};

static GSList *scan(struct sr_dev_driver *di, GSList *options)
{
	struct sr_dev_inst* sdi;
	GSList *devices;
	uint32_t dev_count;

	(void)options;

	if(libauris_device_b480_getcount(&dev_count) != LIBAURIS_DEVICE_RET_OK){
		return NULL;
	}

	devices = NULL;
    for(uint32_t dev_idx=0; dev_idx<dev_count; dev_idx++){
		sdi = g_malloc0(sizeof(struct sr_dev_inst));
		sdi->driver = &auris_b480_driver_info;
		sdi->status = SR_ST_INACTIVE;
		sdi->inst_type = SR_INST_USB;
		sdi->vendor = g_strdup("AURIS");
		sdi->model = g_strdup("B-480");
		sdi->version = NULL;
		sdi->serial_num = g_strdup("TODO");
		sdi->connection_id = g_strdup("TODO");
		for(int i = 0 ; i < 8; i++) {
			sr_channel_new(sdi, i, SR_CHANNEL_ANALOG, TRUE, channel_names[i]);
		}
		sdi->channel_groups = NULL;
	
		sdi->conn = NULL;
		sdi->priv = g_malloc0(sizeof(struct dev_context));
		sdi->session = NULL;

		devices = g_slist_append(devices, sdi);
	}

	return std_scan_complete(di, devices);
}

static int dev_open(struct sr_dev_inst *sdi)
{
	(void)sdi;

	/* TODO: get handle from sdi->conn and open it. */

	return SR_OK;
}

static int dev_close(struct sr_dev_inst *sdi)
{
	(void)sdi;

	/* TODO: get handle from sdi->conn and close it. */

	return SR_OK;
}

static int config_get(uint32_t key, GVariant **data,
	const struct sr_dev_inst *sdi, const struct sr_channel_group *cg)
{
	int ret;

	(void)sdi;
	(void)data;
	(void)cg;

	ret = SR_OK;
	switch (key) {
	/* TODO */
	default:
		return SR_ERR_NA;
	}

	return ret;
}

static int config_set(uint32_t key, GVariant *data,
	const struct sr_dev_inst *sdi, const struct sr_channel_group *cg)
{
	int ret;

	(void)sdi;
	(void)data;
	(void)cg;

	ret = SR_OK;
	switch (key) {
	/* TODO */
	default:
		ret = SR_ERR_NA;
	}

	return ret;
}

static int config_list(uint32_t key, GVariant **data,
	const struct sr_dev_inst *sdi, const struct sr_channel_group *cg)
{
	switch (key) {
	case SR_CONF_SCAN_OPTIONS:
	case SR_CONF_DEVICE_OPTIONS:
		return STD_CONFIG_LIST(key, data, sdi, cg, scanopts, drvopts, devopts);
	default:
		return SR_ERR_NA;
	}

	return SR_OK;
}

static int dev_acquisition_start(const struct sr_dev_inst *sdi)
{
	/* TODO: configure hardware, reset acquisition state, set up
	 * callbacks and send header packet. */

	(void)sdi;

	return SR_OK;
}

static int dev_acquisition_stop(struct sr_dev_inst *sdi)
{
	/* TODO: stop acquisition. */

	(void)sdi;

	return SR_OK;
}

static struct sr_dev_driver auris_b480_driver_info = {
	.name = "auris-b480",
	.longname = "Auris B-480",
	.api_version = 1,
	.init = std_init,
	.cleanup = std_cleanup,
	.scan = scan,
	.dev_list = std_dev_list,
	.dev_clear = std_dev_clear,
	.config_get = config_get,
	.config_set = config_set,
	.config_list = config_list,
	.dev_open = dev_open,
	.dev_close = dev_close,
	.dev_acquisition_start = dev_acquisition_start,
	.dev_acquisition_stop = dev_acquisition_stop,
	.context = NULL,
};
SR_REGISTER_DEV_DRIVER(auris_b480_driver_info);
