/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pci.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:56:36 by ecaceres          #+#    #+#             */
/*   Updated: 2023/02/05 18:56:36 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PCI_HPP_
# define PCI_HPP_

# include <types.h>

namespace kfs::pci
{
	typedef struct
	{
			uint32_t id;
			const char *name;
	} subclass_t;

	typedef struct
	{
			uint32_t id;
			const char *name;
	} class_t;

	typedef struct
	{
			uint32_t vendor;
			uint32_t device;
			uint32_t func;
			class_t class_;
			subclass_t subclass;
	} device_t;

	typedef struct
	{
			uint32_t id;
			const char *name;
			subclass_t sub[129];
	} class_info_t;

	extern class_info_t class_infos[];
	extern device_t devices[];
	extern uint32_t device_count;

	void initialize(void);

	void probe(void);
	bool add(uint16_t bus, uint8_t slot, uint8_t func);

	uint16_t read_vendor_id(uint8_t bus, uint8_t slot, uint8_t func);
	uint16_t read_device_id(uint8_t bus, uint8_t slot, uint8_t func);
	uint8_t read_device_class_id(uint8_t bus, uint8_t slot, uint8_t func);
	uint8_t read_device_subclass_id(uint8_t bus, uint8_t slot, uint8_t func);
	uint32_t read_dword(uint8_t bus, uint8_t slot, uint8_t func, uint8_t reg);
}

#endif /* PCI_HPP_ */
