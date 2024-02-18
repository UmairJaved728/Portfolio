import {useState} from 'react'
import {
    TextField,
    Text,
    ScrollView,
    VStack,
    Center,
    Image,
    Box,
    IconButton,
    Button,
    Input,
    HStack,
    Divider,
    FormControl
} from "native-base";
import React from "react";
import {SafeAreaView} from "react-native-safe-area-context";
import {THEME} from "../theme";
import {ButtonToken} from "../components/ButtonToken";
import {ResturantLogo} from "../components/ResturantLogo";
import {Eye, EyeSlash} from 'phosphor-react-native'
import {Checkbox} from "../components/Checkbox";
import {TouchableOpacity} from "react-native";
import GooglLogo from "../assets/iconGoogle.png";
import Logo from "../assets/resturantLogo.png";

export function ForgotPassword() {
    const [isLoading, setIsLoading] = useState(false)

    return (
        <SafeAreaView>
            <ScrollView
                contentContainerStyle={{flexGrow: 1}}
                showsVerticalScrollIndicator={false}
            >
                <VStack flex={1}>
                    <Box
                        h={556}
                        borderBottomRadius={24}
                        pt={'50px'}
                        pb={'68px'}
                        px={'40px'}
                        mb={'10%'}
                        bgColor={THEME.colors.Primary[100]}
                    >
                        <Center>
                            <ResturantLogo width={24} height={24}/>
                            <Text textAlign={'center'} fontFamily={THEME.Fonts.heading}
                                  color={THEME.colors.Primary[700]}
                                  mt={'8%'} fontSize={THEME.FontSizes.xxl}>
                                Forgot Password
                            </Text>
                            <Text marginTop={'10px'} marginBottom={'20px'} fontFamily={THEME.Fonts.body}
                                  fontSize={THEME.FontSizes.md} color={THEME.colors.Primary[300]}>
                                Don’t worry! It happens. Please enter the email associated with your account.
                            </Text>
                            {/*<Controller*/}
                            {/*    control={control}*/}
                            {/*    name="password"*/}
                            {/*    render={({field: {onChange, value}}) => (*/}
                            <Input
                                placeholder="Enter Your Email"
                                keyboardType="email-address"
                                autoCapitalize="none"
                                bgColor={THEME.colors.Primary[50]}
                                borderRadius="6px"
                                borderColor={THEME.colors.Primary[100]}
                                paddingX={'12px'}
                                paddingY={'16px'}
                                fontSize={THEME.FontSizes.md}
                                // onChangeText={onChange}
                                // value={value}
                            />
                            {/*    )}*/}
                            {/*/>*/}

                            {/*<ErrorMessage*/}
                            {/*    errors={errors}*/}
                            {/*    name="password"*/}
                            {/*    render={({message}) => (*/}
                            {/*        <Text color={THEME.colors.Danger[500]} fontFamily={THEME.Fonts.heading}*/}
                            {/*              style={{marginTop: -15}}>*/}
                            {/*            {message}*/}
                            {/*        </Text>*/}
                            {/*    )}*/}
                            {/*/>*/}
                            <ButtonToken
                                message="Send Code"
                                width={'full'}
                                onPress={() => {
                                }}
                                variant={'GREEN'}
                                mt={'20px'}
                                isLoading={isLoading}
                                _text={{fontSize: THEME.FontSizes.md}}
                            />
                        </Center>
                    </Box>
                    <Center>
                        <HStack mt={'20px'} width={'98%'} alignItems={'center'} justifyContent={'center'}>
                            <VStack mt={'1%'} marginRight={'1%'} marginLeft={'1%'}>
                                <Text color={THEME.colors.Primary[400]} fontSize={THEME.FontSizes.sm}>Remember Password?</Text>
                            </VStack>

                            <TouchableOpacity
                                // onPress={handleCreateAccountPress}
                            >
                                <Text fontFamily={THEME.Fonts.body} fontSize={THEME.FontSizes.sm} marginTop={'3px'}
                                      marginLeft={'5px'}
                                      color={'blue.500'}>Login</Text>
                            </TouchableOpacity>
                        </HStack>
                        <HStack>
                            <Image
                                source={Logo}
                                width={'10px'}
                                height={'10px'}
                                rounded="full"
                                borderWidth={5}
                                alt="App Logo"
                            />
                        </HStack>
                    </Center>
                </VStack>
            </ScrollView>
        </SafeAreaView>
    )
}
