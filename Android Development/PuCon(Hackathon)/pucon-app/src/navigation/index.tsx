import {useTheme, Box, HStack, Pressable, Image, VStack} from 'native-base'
import {NavigationContainer, DefaultTheme, useNavigation} from '@react-navigation/native'

// import {Loading} from '@components/Loading'
//
import {AuthRoutes} from './auth.routes'
import {THEME} from "../theme";
import {AppRoutes, DrawerNavigatorRoutesProps} from './app.routes'
import {useAuth} from "../context/AuthContext";
import {List} from "phosphor-react-native";
import {LargeLogo} from "../components/LargeLogo";
import User from "../assets/user.png";
import React from "react";
// import {useAuth} from '@hooks/useAuth'
// import {THEME} from "@theme/index";

export function Routes() {
    const {colors} = useTheme()

    const theme = DefaultTheme
    theme.colors.background = THEME.colors.Primary[100]

    const {user} = useAuth()

    return (
        <Box flex={1} bg={THEME.colors.Primary[100]}>
            <NavigationContainer theme={theme}>
                {user?.email ?
                        <AppRoutes />
                    :
                    <AuthRoutes/>}
            </NavigationContainer>
        </Box>
    )
}
