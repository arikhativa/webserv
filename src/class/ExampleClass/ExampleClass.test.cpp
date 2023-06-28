/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExampleClass.test.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrabby <yrabby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:00:27 by yrabby            #+#    #+#             */
/*   Updated: 2023/06/28 13:49:47 by yrabby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include <ExampleClass/ExampleClass.hpp>

TEST(ExampleClass, getValue)
{
	int val(6);
	ExampleClass i(val);
	EXPECT_EQ(val, i.getValue());
	EXPECT_EQ(val, 6);
}

TEST(ExampleClass, _setValue)
{
	ExampleClass i;
	i._setValue(7);
	EXPECT_EQ(i.getValue(), 7);
}
