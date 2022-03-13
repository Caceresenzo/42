/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 00:35:02 by ecaceres          #+#    #+#             */
/*   Updated: 2022/03/13 00:35:02 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP_
# define NODE_HPP_

#include <engine/math/Transform.hpp>
#include <lang/reference/SharedReference.hpp>
#include <lang/reference/WeakReference.hpp>
#include <vector>

class Node
{
	public:
		typedef std::vector<SharedReference<Node> > node_vector;

	private:
		long m_id;

	public:
		Node *parent;
		node_vector children;
		Transform<float> transform;

	public:
		Node();

		virtual
		~Node();

	public:
		SharedReference<Node>
		add_child(Node &node);

		template<typename T>
			T&
			add_child_as(T &node)
			{
				return (reinterpret_cast<T&>(*add_child(node)));
			}

		SharedReference<Node>
		remove_child(Node &node);

		virtual void
		render();

	public:
		inline long
		id()
		{
			return (m_id);
		}

	public:
		static void
		dump(Node &root, long depth = 0);
};

#endif /* NODE_HPP_ */
