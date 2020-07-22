/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 15:16:05 by ecaceres          #+#    #+#             */
/*   Updated: 2020/07/22 15:16:05 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AsteroKreog.hpp"
#include "DeepCoreMiner.hpp"
#include "KoalaSteroid.hpp"
#include "MiningBarge.hpp"
#include "StripMiner.hpp"

void
do_mining(MiningBarge &barge)
{
	AsteroKreog asteroid1; /* Asteroid */
	KoalaSteroid asteroid2; /* Comet */

	std::cout << "-- Mining: AsteroKreog (asteriod)" << std::endl;
	barge.mine(&asteroid1);

	std::cout << std::endl << "-- Mining: KoalaSteroid (comet)" << std::endl;
	barge.mine(&asteroid2);
}

int
main(void)
{
	StripMiner miner1;
	DeepCoreMiner miner2;
	DeepCoreMiner miner3;
	StripMiner miner4;
	DeepCoreMiner miner5;

	MiningBarge barge;

	std::cout << "Laser count: 0" << std::endl;
	do_mining(barge);

	barge.equip(&miner1);

	std::cout << std::endl << std::endl << "==== Laser count: 1" << std::endl << std::endl;
	do_mining(barge);

	barge.equip(&miner2);

	std::cout << std::endl << std::endl << "==== Laser count: 2" << std::endl << std::endl;
	do_mining(barge);

	barge.equip(&miner3);

	std::cout << std::endl << std::endl << "==== Laser count: 3" << std::endl << std::endl;
	do_mining(barge);

	barge.equip(&miner4);

	std::cout << std::endl << std::endl << "==== Laser count: 4" << std::endl << std::endl;
	do_mining(barge);

	barge.equip(&miner5);

	std::cout << std::endl << std::endl << "==== Laser count: 5?" << std::endl << std::endl;
	do_mining(barge);
}
