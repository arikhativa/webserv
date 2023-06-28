/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrabby <yrabby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:25:39 by yrabby            #+#    #+#             */
/*   Updated: 2023/06/28 11:50:28 by yrabby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <main/main.hpp>

int main(void)
{
	ExampleClass a(42);
	std::cout << a << std::endl;

	ExampleTemplate<long> b(-42);
	std::cout << b << std::endl;
	return (0);
}
