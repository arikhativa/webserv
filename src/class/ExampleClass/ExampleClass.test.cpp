/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExampleClass.test.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrabby <yrabby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:00:27 by yrabby            #+#    #+#             */
/*   Updated: 2023/06/28 13:08:11 by yrabby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <ExampleClass/ExampleClass.hpp>

TEST(ExampleClassTester, getValue)
{
	int val(6);
	ExampleClass i(val);
	EXPECT_EQ(val, i.getValue());
	EXPECT_EQ(val, 6);
}
