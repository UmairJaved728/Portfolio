import {TextField, Text, ScrollView, VStack, Center, Image, Box, IconButton, Button} from "native-base";
import React from "react";
import {SafeAreaView} from "react-native-safe-area-context";
import Logo from '../assets/resturantLogo.png'
import {THEME} from "../theme";
import {ButtonToken} from "../components/ButtonToken";
import {ResturantLogo} from "../components/ResturantLogo";
import {useNavigation} from "@react-navigation/native";
import {AuthNavigatorRoutesProps} from "../navigation/auth.routes";

export function SplashScreen() {

    const navigation = useNavigation<AuthNavigatorRoutesProps>()

    function handleLoginPress() {
        navigation.navigate('signIn')
    }

    function handleSignupPress() {
        navigation.navigate('signUp')
    }

    return (
        <SafeAreaView>
            <ScrollView
                contentContainerStyle={{flexGrow: 1}}
                showsVerticalScrollIndicator={false}
            >
                <VStack flex={1}>
                    <Box
                        h={490}
                        borderBottomRadius={24}
                        pt={'68px'}
                        px={'48px'}
                    >
                        <Center>
                            <ResturantLogo width={40} height={40}/>
                            <Text textAlign={'center'} fontFamily={THEME.Fonts.heading}
                                  color={THEME.colors.Primary[700]}
                                  mt={'8%'} fontSize={40}>
                                ARestro
                            </Text>
                        </Center>
                    </Box>
                    <Center px={'48px'} mb={'5%'}>
                        <ButtonToken
                            message="Login"
                            onPress={handleLoginPress}
                            variant={'GREEN'}
                            width={'100%'}
                            flex={1}
                            fontSize={THEME.FontSizes.md}
                            _text={{fontSize: THEME.FontSizes.md}}
                        />
                        <Button
                            mt={'20px'}
                            borderRadius={'6px'}
                            borderWidth={'1px'}
                            borderColor={THEME.colors.Primary[300]}
                            fontSize={THEME.FontSizes.sm}
                            onPress={handleSignupPress}
                            width={'100%'}
                            backgroundColor={THEME.colors.Primary[100]}
                            _text={{color: THEME.colors.Primary[300], fontSize: THEME.FontSizes.md}}
                        >
                            SignUp
                        </Button>
                    </Center>
                </VStack>
            </ScrollView>
        </SafeAreaView>
    )
}
