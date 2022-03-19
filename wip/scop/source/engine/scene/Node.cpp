/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 00:35:02 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/13 00:35:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <lang/IllegalArgumentException.hpp>
#include <engine/scene/Node.hpp>
#include <iostream>
#include <iterator>
#include <typeinfo>

static long global_id = 0;

Node::Node() :
		m_id(++global_id),
		parent(NULL)
{
}

Node::~Node()
{
}

SharedReference<Node>
Node::add_child(Node &node)
{
	if (&node == this)
		throw IllegalArgumentException("cannot set parent to itself");

	if (node.parent)
		throw IllegalArgumentException("already have a parent");

	node.parent = this;

	SharedReference<Node> reference(node);
	children.push_back(reference);

	return (reference);
}

SharedReference<Node>
Node::remove_child(Node &node)
{
	if (this == &node)
		return (SharedReference<Node>());

	for (node_vector::iterator iterator = children.begin(); iterator != children.end(); ++iterator)
		if (iterator->value() == &node)
		{
			SharedReference<Node> reference = *iterator;

			node.parent = NULL;
			children.erase(iterator);

			return (reference);
		}

	return (SharedReference<Node>());
}

void
Node::update(double delta_time)
{
	for (node_vector::iterator iterator = children.begin(); iterator != children.end(); ++iterator)
		(**iterator).update(delta_time);
}

void
Node::render()
{
	for (node_vector::iterator iterator = children.begin(); iterator != children.end(); ++iterator)
		(**iterator).render();
}

void
Node::dump(Node &root, long depth)
{
	if (depth == 0)
		std::cout << typeid(root).name() << "(" << root.m_id << ", " << &root << ")" << std::endl;

	for (node_vector::iterator iterator = root.children.begin(); iterator != root.children.end(); ++iterator)
	{
		Node &node = **iterator;

		for (long i = 0; i < (depth + 1); ++i)
			std::cout << "  ";

		const char *linkage = node.parent == &root ? "linked" : "error";
		std::cout << typeid(node).name() << "(" << node.m_id << ", " << &node << ", " << &*node.parent << '=' << linkage << ")" << std::endl;

		dump(node, depth + 1);
	}
}
