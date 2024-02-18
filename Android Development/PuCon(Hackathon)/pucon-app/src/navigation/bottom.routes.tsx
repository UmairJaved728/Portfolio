import {BottomTabNavigationProp, createBottomTabNavigator} from "@react-navigation/bottom-tabs"
import {THEME} from '../theme'
import {Platform} from "react-native";
import React from "react";
import {House, MagnifyingGlass} from "phosphor-react-native";
import {Home} from "../screens/Home";
import {Text, useTheme, VStack} from "native-base";
import {Search} from "../screens/Search";
import {ProductDTO} from "../dto/productDTO";
import {FoodOrder} from "../screens/FoodOrder";
import {RestaurantDTO} from "../dto/restaurantDTO";
import {RestaurantDetails} from "../screens/RestaurantDetails";

export type TBottomRoutes = {
    home: undefined
    search: undefined
    foodOrder: ProductDTO
    restaurantDetails: RestaurantDTO
}

export type BottomNavigatorRoutesProps = BottomTabNavigationProp<TBottomRoutes>

const {Navigator, Screen} = createBottomTabNavigator<TBottomRoutes>()

export function BottomRoutes() {
    const {sizes, colors} = useTheme()
    return (
        <Navigator
            screenOptions={{
                headerShown: false,
                tabBarShowLabel: false,
                tabBarActiveTintColor: THEME.colors.Primary[700],
                tabBarInactiveTintColor: THEME.colors.Primary[200],
                tabBarStyle: {
                    backgroundColor: THEME.colors.Primary[100],
                    borderTopWidth: 0,
                    height: Platform.OS === 'android' ? 'auto' : 96,
                    paddingBottom: sizes[8],
                    paddingTop: sizes[6],
                    alignContent: 'center',
                },
            }}
        >
            <Screen
                name="home"
                component={Home}
                options={{
                    tabBarIcon: ({color}) => (<VStack><House size={16} color={color}/><Text>Home</Text></VStack>),
                }}
            />
            <Screen
                name="search"
                component={Search}
                options={{
                    tabBarIcon: ({color}) => (<VStack><MagnifyingGlass size={16} color={color}/><Text>Home</Text></VStack>),
                }}
            />

            <Screen
                name={"foodOrder"}
                component={FoodOrder}
                options={{
                    tabBarButton: () => null,
                    tabBarShowLabel: false,
                    tabBarStyle: {display: 'none'},
                }}
            />

            <Screen
                name={"restaurantDetails"}
                component={RestaurantDetails}
                options={{
                    tabBarButton: () => null,
                    tabBarShowLabel: false,
                    tabBarStyle: {display: 'none'},
                }}
            />
        </Navigator>

    );
}
