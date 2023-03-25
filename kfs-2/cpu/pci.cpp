/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pci.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:49:26 by ecaceres          #+#    #+#             */
/*   Updated: 2023/02/05 18:49:26 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cpu/io.hpp>
#include <cpu/pci.hpp>
#include <string.h>

# define PCI_CONFIG_ADDR 0xcf8
# define PCI_CONFIG_DATA 0xcfc
# define PCI_REGISTRY_MAX 28

namespace kfs::pci
{
	device_t devices[PCI_REGISTRY_MAX];
	uint32_t device_count = 0;

	void initialize(void)
	{
		device_count = 0;
		probe();
	}

	void probe(void)
	{
		for (uint16_t bus = 0; bus < 256; ++bus)
			for (uint8_t slot = 0; slot < 32; ++slot)
				for (uint8_t func = 0; func < 8; ++func)
					add(bus, slot, func);
	}

	class_info_t* get_class_info(uint32_t class_id)
	{
		for (class_info_t *info = class_infos; info->id != -1; ++info)
		{
			if (info->id == class_id)
				return (info);
		}

		return (NULL);
	}

	subclass_t* get_subclass_info(class_info_t *info, uint32_t subclass_id)
	{
		if (info == NULL)
			return (NULL);

		for (subclass_t *sub = info->sub; sub->id != -1; ++sub)
		{
			if (sub->id == subclass_id)
				return (sub);
		}

		return (NULL);
	}

	bool add(uint16_t bus, uint8_t slot, uint8_t func)
	{
		uint16_t vendor_id = read_vendor_id(bus, slot, func);
		if (vendor_id == 0xFFFF)
			return (false);

		if (device_count < PCI_REGISTRY_MAX)
		{
			device_t *entry = devices + device_count;
			entry->vendor = vendor_id;
			entry->device = read_device_id(bus, slot, func);
			entry->func = func;

			uint32_t class_id = read_device_class_id(bus, slot, func);
			entry->class_.id = class_id;
			entry->class_.name = NULL;

			uint32_t subclass_id = read_device_subclass_id(bus, slot, func);
			entry->subclass.id = subclass_id;
			entry->subclass.name = NULL;

			class_info_t *info = get_class_info(class_id);
			if (info)
			{
				entry->class_.name = info->name;

				subclass_t *sub = get_subclass_info(info, subclass_id);
				if (sub)
					entry->subclass.name = sub->name;
			}

			device_count++;
			return (true);
		}

		return (false);
	}

	uint16_t read_vendor_id(uint8_t bus, uint8_t slot, uint8_t func)
	{
		return (read_dword(bus, slot, func, 0) & 0xffff);
	}

	uint16_t read_device_id(uint8_t bus, uint8_t slot, uint8_t func)
	{
		return ((read_dword(bus, slot, func, 0) >> 16) & 0xffff);
	}

	uint8_t read_device_class_id(uint8_t bus, uint8_t slot, uint8_t func)
	{
		return ((read_dword(bus, slot, func, 2) >> 24) & 0xff);
	}

	uint8_t read_device_subclass_id(uint8_t bus, uint8_t slot, uint8_t func)
	{
		return ((read_dword(bus, slot, func, 2) >> 16) & 0xff);
	}

	uint32_t read_dword(uint8_t bus, uint8_t slot, uint8_t func, uint8_t reg)
	{
		uint32_t lbus = (uint32_t)bus;
		uint32_t lslot = (uint32_t)slot;
		uint32_t lfunc = (uint32_t)func;

		uint32_t address = (uint32_t)((lbus << 16)
			| ((lslot & 0b00011111) << 11)
			| ((lfunc & 0b00000111) << 8)
			| (reg << 2) /* Register to offset. */
			| ((uint32_t)(1 << 31)));

		kfs::io::outl(PCI_CONFIG_ADDR, address);
		return (kfs::io::inl(PCI_CONFIG_DATA));
	}

	class_t get_class(uint32_t class_id)
	{
		class_t class_;
		class_.id = class_id;
		class_.name = NULL;

		class_info_t *info = get_class_info(class_id);
		for (class_info_t *info = class_infos; info->id != -1; ++info)
		{
			if (info->id == class_id)
			{
				class_.name = info->name;
				break;
			}
		}

		return (class_);
	}

#define RESERVED_CLASS(id_value) { .id = id_value, .name = "(Reserved)", .sub = { { 0, 0 } } }

	class_info_t class_infos[] = {
		{
			.id = 0x00,
			.name = "Unclassified",
			.sub = {
				{ .id = 0x00, .name = "Non-VGA-Compatible devices" },
				{ .id = 0x01, .name = "VGA-Compatible Device" },
				{ (uint32_t)-1, 0 },
			},
		},
		{
			.id = 0x01,
			.name = "Mass Storage Controller",
			.sub = {
				{ .id = 0x00, .name = "SCSI Bus Controller" },
				{ .id = 0x01, .name = "IDE Controller" },
				{ .id = 0x02, .name = "Floppy Disk Controller" },
				{ .id = 0x03, .name = "IPI Bus Controller" },
				{ .id = 0x04, .name = "RAID Controller" },
				{ .id = 0x05, .name = "ATA Controller" },
				{ .id = 0x06, .name = "Serial ATA" },
				{ .id = 0x07, .name = "Serial Attached SCSI" },
				{ .id = 0x08, .name = "Non-Volatile Memory Controller" },
				{ .id = 0x80, .name = "Other" },
				{ (uint32_t)-1, 0 },
			},
		},
		{
			.id = 0x02,
			.name = "Network Controller",
			.sub = {
				{ .id = 0x00, .name = "Ethernet Controller" },
				{ .id = 0x01, .name = "Token Ring Controller" },
				{ .id = 0x02, .name = "FDDI Controller" },
				{ .id = 0x03, .name = "ATM Controller" },
				{ .id = 0x04, .name = "ISDN Controller" },
				{ .id = 0x05, .name = "WorldFip Controller" },
				{ .id = 0x06, .name = "PICMG 2.14 Multi Computing" },
				{ .id = 0x07, .name = "Infiniband Controller" },
				{ .id = 0x08, .name = "Fabric Controller" },
				{ .id = 0x80, .name = "Other" },
				{ (uint32_t)-1, 0 },
			},
		},
		{
			.id = 0x03,
			.name = "Display Controller",
			.sub = {
				{ .id = 0x00, .name = "VGA Compatible Controller" },
				{ .id = 0x01, .name = "XGA Controller" },
				{ .id = 0x02, .name = "3D Controller (Not VGA-Compatible)" },
				{ .id = 0x80, .name = "Other" },
				{ (uint32_t)-1, 0 },
			},
		},
		{
			.id = 0x04,
			.name = "Multimedia Controller",
			.sub = {
				{ .id = 0x00, .name = "Multimedia Video Controller" },
				{ .id = 0x01, .name = "Multimedia Audio Controller" },
				{ .id = 0x02, .name = "Computer Telephony Device" },
				{ .id = 0x03, .name = "Audio Device" },
				{ .id = 0x80, .name = "Other" },
				{ (uint32_t)-1, 0 },
			},
		},
		{
			.id = 0x05,
			.name = "Memory Controller",
			.sub = {
				{ .id = 0x00, .name = "RAM Controller" },
				{ .id = 0x01, .name = "Flash Controller" },
				{ .id = 0x80, .name = "Other" },
				{ (uint32_t)-1, 0 },
			},
		},
		{
			.id = 0x06,
			.name = "Bridge Device",
			.sub = {
				{ .id = 0x00, .name = "Host Bridge" },
				{ .id = 0x01, .name = "ISA Bridge" },
				{ .id = 0x02, .name = "EISA Bridge" },
				{ .id = 0x03, .name = "MCA Bridge" },
				{ .id = 0x04, .name = "PCI-to-PCI Bridge" },
				{ .id = 0x05, .name = "PCMCIA Bridge" },
				{ .id = 0x06, .name = "NuBus Bridge" },
				{ .id = 0x07, .name = "CardBus Bridge" },
				{ .id = 0x08, .name = "RACEway Bridge" },
				{ .id = 0x09, .name = "PCI-to-PCI Bridge" },
				{ .id = 0x0a, .name = "InfiniBand-to-PCI Host Bridge" },
				{ .id = 0x80, .name = "Other" },
				{ (uint32_t)-1, 0 },
			},
		},
		{
			.id = 0x07,
			.name = "Simple Communication Controller",
			.sub = {
				{ .id = 0x00, .name = "Serial Controller" },
				{ .id = 0x01, .name = "Parallel Controller" },
				{ .id = 0x02, .name = "Multiport Serial Controller" },
				{ .id = 0x03, .name = "Modem" },
				{ .id = 0x04, .name = "IEEE 488.1/2 (GPIB) Controller" },
				{ .id = 0x05, .name = "Smart Card" },
				{ .id = 0x80, .name = "Other" },
				{ (uint32_t)-1, 0 },
			},
		},
		{
			.id = 0x08,
			.name = "Base System Peripheral",
			.sub = {
				{ .id = 0x00, .name = "PIC" },
				{ .id = 0x01, .name = "DMA Controller" },
				{ .id = 0x02, .name = "Timer" },
				{ .id = 0x03, .name = "RTC Controller" },
				{ .id = 0x04, .name = "PCI Hot-Plug Controller" },
				{ .id = 0x05, .name = "SD Host controller" },
				{ .id = 0x06, .name = "IOMMU" },
				{ .id = 0x80, .name = "Other" },
				{ (uint32_t)-1, 0 },
			},
		},
		{
			.id = 0x09,
			.name = "Input Device Controller",
			.sub = {
				{ .id = 0x00, .name = "Keyboard Controller" },
				{ .id = 0x01, .name = "Digitizer Pen" },
				{ .id = 0x02, .name = "Mouse Controller" },
				{ .id = 0x03, .name = "Scanner Controller" },
				{ .id = 0x04, .name = "Gameport Controller" },
				{ .id = 0x80, .name = "Other" },
				{ (uint32_t)-1, 0 },
			},
		},
		{
			.id = 0x0a,
			.name = "Docking Station",
			.sub = {
				{ .id = 0x00, .name = "Generic" },
				{ .id = 0x80, .name = "Other" },
				{ (uint32_t)-1, 0 },
			},
		},
		{
			.id = 0x0b,
			.name = "Processor",
			.sub = {
				{ .id = 0x00, .name = "386" },
				{ .id = 0x01, .name = "486" },
				{ .id = 0x02, .name = "Pentium" },
				{ .id = 0x03, .name = "Pentium Pro" },
				{ .id = 0x10, .name = "Alpha" },
				{ .id = 0x20, .name = "PowerPC" },
				{ .id = 0x30, .name = "MIPS" },
				{ .id = 0x40, .name = "Co-Processor" },
				{ .id = 0x80, .name = "Other" },
				{ (uint32_t)-1, 0 },
			},
		},
		{
			.id = 0x0c,
			.name = "Serial Bus Controller",
			.sub = {
				{ .id = 0x00, .name = "FireWire (IEEE 1394) Controller" },
				{ .id = 0x01, .name = "ACCESS Bus" },
				{ .id = 0x02, .name = "SSA" },
				{ .id = 0x03, .name = "USB Controller" },
				{ .id = 0x04, .name = "Fibre Channel" },
				{ .id = 0x05, .name = "SMBus" },
				{ .id = 0x06, .name = "InfiniBand" },
				{ .id = 0x07, .name = "IPMI Interface" },
				{ .id = 0x08, .name = "SERCOS Interface (IEC 61491)" },
				{ .id = 0x09, .name = "CANbus" },
				{ .id = 0x80, .name = "Other" },
				{ (uint32_t)-1, 0 },
			},
		},
		{
			.id = 0x0d,
			.name = "Wireless Controller",
			.sub = {
				{ .id = 0x00, .name = "iRDA Compatible Controller" },
				{ .id = 0x01, .name = "Consumer IR Controller" },
				{ .id = 0x10, .name = "RF Controller" },
				{ .id = 0x11, .name = "Bluetooth Controller" },
				{ .id = 0x12, .name = "Broadband Controller" },
				{ .id = 0x20, .name = "Ethernet Controller (802.1a)" },
				{ .id = 0x21, .name = "Ethernet Controller (802.1b)" },
				{ .id = 0x80, .name = "Other" },
				{ (uint32_t)-1, 0 },
			},
		},
		{
			.id = 0x0e,
			.name = "Intelligent Controller",
			.sub = {
				{ .id = 0x20, .name = "I20" },
				{ (uint32_t)-1, 0 },
			},
		},
		{
			.id = 0x0f,
			.name = "Satellite Communication Controller",
			.sub = {
				{ .id = 0x01, .name = "Satellite TV Controller" },
				{ .id = 0x02, .name = "Satellite Audio Controller" },
				{ .id = 0x03, .name = "Satellite Voice Controller" },
				{ .id = 0x04, .name = "Satellite Data Controller" },
				{ (uint32_t)-1, 0 },
			},
		},
		{
			.id = 0x10,
			.name = "Encryption Controller",
			.sub = {
				{ .id = 0x00, .name = "Network and Computing Encrpytion/Decryption" },
				{ .id = 0x10, .name = "Entertainment Encryption/Decryption" },
				{ .id = 0x80, .name = "Other Encryption/Decryption" },
				{ (uint32_t)-1, 0 },
			},
		},
		{
			.id = 0x11,
			.name = "Signal Processing Controller",
			.sub = {
				{ .id = 0x00, .name = "DPIO Modules" },
				{ .id = 0x01, .name = "Performance Counters" },
				{ .id = 0x10, .name = "Communication Synchronizer" },
				{ .id = 0x20, .name = "Signal Processing Management" },
				{ .id = 0x80, .name = "Other" },
				{ (uint32_t)-1, 0 },
			},
		},
		{
			.id = 0x12,
			.name = "Processing Accelerator",
			.sub = {
				{ (uint32_t)-1, 0 },
			},
		},
		{
			.id = 0x13,
			.name = "Non-Essential Instrumentation",
			.sub = {
				{ (uint32_t)-1, 0 },
			},
		},
		RESERVED_CLASS(0x14),
		RESERVED_CLASS(0x15),
		RESERVED_CLASS(0x16),
		RESERVED_CLASS(0x17),
		RESERVED_CLASS(0x18),
		RESERVED_CLASS(0x19),
		RESERVED_CLASS(0x1a),
		RESERVED_CLASS(0x1b),
		RESERVED_CLASS(0x1c),
		RESERVED_CLASS(0x1d),
		RESERVED_CLASS(0x1e),
		RESERVED_CLASS(0x1f),
		RESERVED_CLASS(0x20),
		RESERVED_CLASS(0x21),
		RESERVED_CLASS(0x22),
		RESERVED_CLASS(0x23),
		RESERVED_CLASS(0x24),
		RESERVED_CLASS(0x25),
		RESERVED_CLASS(0x26),
		RESERVED_CLASS(0x27),
		RESERVED_CLASS(0x28),
		RESERVED_CLASS(0x29),
		RESERVED_CLASS(0x2a),
		RESERVED_CLASS(0x2b),
		RESERVED_CLASS(0x2c),
		RESERVED_CLASS(0x2d),
		RESERVED_CLASS(0x2e),
		RESERVED_CLASS(0x2f),
		RESERVED_CLASS(0x30),
		RESERVED_CLASS(0x31),
		RESERVED_CLASS(0x32),
		RESERVED_CLASS(0x33),
		RESERVED_CLASS(0x34),
		RESERVED_CLASS(0x35),
		RESERVED_CLASS(0x36),
		RESERVED_CLASS(0x37),
		RESERVED_CLASS(0x38),
		RESERVED_CLASS(0x39),
		RESERVED_CLASS(0x3a),
		RESERVED_CLASS(0x3b),
		RESERVED_CLASS(0x3c),
		RESERVED_CLASS(0x3d),
		RESERVED_CLASS(0x3e),
		RESERVED_CLASS(0x3f),
		{
			.id = 0x40,
			.name = "Co-Processor",
			.sub = {
				{ (uint32_t)-1, 0 },
			},
		},
		RESERVED_CLASS(0x41),
		RESERVED_CLASS(0x42),
		RESERVED_CLASS(0x43),
		RESERVED_CLASS(0x44),
		RESERVED_CLASS(0x45),
		RESERVED_CLASS(0x46),
		RESERVED_CLASS(0x47),
		RESERVED_CLASS(0x48),
		RESERVED_CLASS(0x49),
		RESERVED_CLASS(0x4a),
		RESERVED_CLASS(0x4b),
		RESERVED_CLASS(0x4c),
		RESERVED_CLASS(0x4d),
		RESERVED_CLASS(0x4e),
		RESERVED_CLASS(0x4f),
		RESERVED_CLASS(0x50),
		RESERVED_CLASS(0x51),
		RESERVED_CLASS(0x52),
		RESERVED_CLASS(0x53),
		RESERVED_CLASS(0x54),
		RESERVED_CLASS(0x55),
		RESERVED_CLASS(0x56),
		RESERVED_CLASS(0x57),
		RESERVED_CLASS(0x58),
		RESERVED_CLASS(0x59),
		RESERVED_CLASS(0x5a),
		RESERVED_CLASS(0x5b),
		RESERVED_CLASS(0x5c),
		RESERVED_CLASS(0x5d),
		RESERVED_CLASS(0x5e),
		RESERVED_CLASS(0x5f),
		RESERVED_CLASS(0x60),
		RESERVED_CLASS(0x61),
		RESERVED_CLASS(0x62),
		RESERVED_CLASS(0x63),
		RESERVED_CLASS(0x64),
		RESERVED_CLASS(0x65),
		RESERVED_CLASS(0x66),
		RESERVED_CLASS(0x67),
		RESERVED_CLASS(0x68),
		RESERVED_CLASS(0x69),
		RESERVED_CLASS(0x6a),
		RESERVED_CLASS(0x6b),
		RESERVED_CLASS(0x6c),
		RESERVED_CLASS(0x6d),
		RESERVED_CLASS(0x6e),
		RESERVED_CLASS(0x6f),
		RESERVED_CLASS(0x70),
		RESERVED_CLASS(0x71),
		RESERVED_CLASS(0x72),
		RESERVED_CLASS(0x73),
		RESERVED_CLASS(0x74),
		RESERVED_CLASS(0x75),
		RESERVED_CLASS(0x76),
		RESERVED_CLASS(0x77),
		RESERVED_CLASS(0x78),
		RESERVED_CLASS(0x79),
		RESERVED_CLASS(0x7a),
		RESERVED_CLASS(0x7b),
		RESERVED_CLASS(0x7c),
		RESERVED_CLASS(0x7d),
		RESERVED_CLASS(0x7e),
		RESERVED_CLASS(0x7f),
		RESERVED_CLASS(0x80),
		RESERVED_CLASS(0x81),
		RESERVED_CLASS(0x82),
		RESERVED_CLASS(0x83),
		RESERVED_CLASS(0x84),
		RESERVED_CLASS(0x85),
		RESERVED_CLASS(0x86),
		RESERVED_CLASS(0x87),
		RESERVED_CLASS(0x88),
		RESERVED_CLASS(0x89),
		RESERVED_CLASS(0x8a),
		RESERVED_CLASS(0x8b),
		RESERVED_CLASS(0x8c),
		RESERVED_CLASS(0x8d),
		RESERVED_CLASS(0x8e),
		RESERVED_CLASS(0x8f),
		RESERVED_CLASS(0x90),
		RESERVED_CLASS(0x91),
		RESERVED_CLASS(0x92),
		RESERVED_CLASS(0x93),
		RESERVED_CLASS(0x94),
		RESERVED_CLASS(0x95),
		RESERVED_CLASS(0x96),
		RESERVED_CLASS(0x97),
		RESERVED_CLASS(0x98),
		RESERVED_CLASS(0x99),
		RESERVED_CLASS(0x9a),
		RESERVED_CLASS(0x9b),
		RESERVED_CLASS(0x9c),
		RESERVED_CLASS(0x9d),
		RESERVED_CLASS(0x9e),
		RESERVED_CLASS(0x9f),
		RESERVED_CLASS(0xa0),
		RESERVED_CLASS(0xa1),
		RESERVED_CLASS(0xa2),
		RESERVED_CLASS(0xa3),
		RESERVED_CLASS(0xa4),
		RESERVED_CLASS(0xa5),
		RESERVED_CLASS(0xa6),
		RESERVED_CLASS(0xa7),
		RESERVED_CLASS(0xa8),
		RESERVED_CLASS(0xa9),
		RESERVED_CLASS(0xaa),
		RESERVED_CLASS(0xab),
		RESERVED_CLASS(0xac),
		RESERVED_CLASS(0xad),
		RESERVED_CLASS(0xae),
		RESERVED_CLASS(0xaf),
		RESERVED_CLASS(0xb0),
		RESERVED_CLASS(0xb1),
		RESERVED_CLASS(0xb2),
		RESERVED_CLASS(0xb3),
		RESERVED_CLASS(0xb4),
		RESERVED_CLASS(0xb5),
		RESERVED_CLASS(0xb6),
		RESERVED_CLASS(0xb7),
		RESERVED_CLASS(0xb8),
		RESERVED_CLASS(0xb9),
		RESERVED_CLASS(0xba),
		RESERVED_CLASS(0xbb),
		RESERVED_CLASS(0xbc),
		RESERVED_CLASS(0xbd),
		RESERVED_CLASS(0xbe),
		RESERVED_CLASS(0xbf),
		RESERVED_CLASS(0xc0),
		RESERVED_CLASS(0xc1),
		RESERVED_CLASS(0xc2),
		RESERVED_CLASS(0xc3),
		RESERVED_CLASS(0xc4),
		RESERVED_CLASS(0xc5),
		RESERVED_CLASS(0xc6),
		RESERVED_CLASS(0xc7),
		RESERVED_CLASS(0xc8),
		RESERVED_CLASS(0xc9),
		RESERVED_CLASS(0xca),
		RESERVED_CLASS(0xcb),
		RESERVED_CLASS(0xcc),
		RESERVED_CLASS(0xcd),
		RESERVED_CLASS(0xce),
		RESERVED_CLASS(0xcf),
		RESERVED_CLASS(0xd0),
		RESERVED_CLASS(0xd1),
		RESERVED_CLASS(0xd2),
		RESERVED_CLASS(0xd3),
		RESERVED_CLASS(0xd4),
		RESERVED_CLASS(0xd5),
		RESERVED_CLASS(0xd6),
		RESERVED_CLASS(0xd7),
		RESERVED_CLASS(0xd8),
		RESERVED_CLASS(0xd9),
		RESERVED_CLASS(0xda),
		RESERVED_CLASS(0xdb),
		RESERVED_CLASS(0xdc),
		RESERVED_CLASS(0xdd),
		RESERVED_CLASS(0xde),
		RESERVED_CLASS(0xdf),
		RESERVED_CLASS(0xe0),
		RESERVED_CLASS(0xe1),
		RESERVED_CLASS(0xe2),
		RESERVED_CLASS(0xe3),
		RESERVED_CLASS(0xe4),
		RESERVED_CLASS(0xe5),
		RESERVED_CLASS(0xe6),
		RESERVED_CLASS(0xe7),
		RESERVED_CLASS(0xe8),
		RESERVED_CLASS(0xe9),
		RESERVED_CLASS(0xea),
		RESERVED_CLASS(0xeb),
		RESERVED_CLASS(0xec),
		RESERVED_CLASS(0xed),
		RESERVED_CLASS(0xee),
		RESERVED_CLASS(0xef),
		RESERVED_CLASS(0xf0),
		RESERVED_CLASS(0xf1),
		RESERVED_CLASS(0xf2),
		RESERVED_CLASS(0xf3),
		RESERVED_CLASS(0xf4),
		RESERVED_CLASS(0xf5),
		RESERVED_CLASS(0xf6),
		RESERVED_CLASS(0xf7),
		RESERVED_CLASS(0xf8),
		RESERVED_CLASS(0xf9),
		RESERVED_CLASS(0xfa),
		RESERVED_CLASS(0xfb),
		RESERVED_CLASS(0xfc),
		RESERVED_CLASS(0xfd),
		RESERVED_CLASS(0xfe),
		{
			.id = 0xff,
			.name = "Unassigned Class (Vendor specific)",
			.sub = {
				{ (uint32_t)-1, 0 },
			},
		},
		{ .id = (uint32_t)-1, .name = NULL, .sub = { { (uint32_t)-1, 0 }, }, },
	};
}
