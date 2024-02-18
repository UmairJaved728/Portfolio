import {Text, ScrollView, VStack, Center, Input, Button, Box, HStack, Divider, Image, useToast} from "native-base";
import React, { useState } from "react";
import {SafeAreaView} from "react-native-safe-area-context";
import {THEME} from "../theme";
import {Controller, FieldValues, useForm} from 'react-hook-form'
import * as yup from 'yup'
import {yupResolver} from '@hookform/resolvers/yup'
import {ErrorMessage} from '@hookform/error-message'
import {Eye, EyeSlash} from 'phosphor-react-native'
import {ResturantLogo} from "../components/ResturantLogo";
import {ButtonToken} from '../components/ButtonToken'
import {useAuth} from '../context/AuthContext'
import {useNavigation} from "@react-navigation/native";
import {AuthNavigatorRoutesProps} from "../navigation/auth.routes";
import GooglLogo from "../assets/iconGoogle.png";
import {TouchableOpacity} from "react-native";

interface FormDataProps {
    username: string
    email: string
    phone: string
    password: string
}

const signUpSchema = yup.object({
    username: yup.string().required('User name cannot be empty'),
    email: yup.string().required('E-mail cannot be empty').email('Invalid Email!.'),
    phone: yup
        .string()
        .matches(
            /^\d{11}$/,
            'Invalid phone number! must be an 11 digit number',
        )
        .required('Phone number cannot be empty'),
    password: yup
        .string()
        .min(8, 'Password must be at least 8 characters long')
        .max(30, 'Password must be at most 30 characters long')
        .matches(
            /^(?=.*[a-z])(?=.*[A-Z])(?=.*[0-9])(?=.*[!@#\$%\^&\*])/,
            'The password must contain at least one uppercase letter, one lowercase letter, one number and one special character.',
        )
        .required('Password cannot be empty')
})

export function Signup() {
    const [isSubmitting, setIsSubmitting] = useState(false)
    const [showPassword, setShowPassword] = useState(false)
    const navigation = useNavigation<AuthNavigatorRoutesProps>()

    const {
        control,
        handleSubmit,
        formState: {errors},
    } = useForm<FormDataProps>({
        resolver: yupResolver(signUpSchema),
    })

    function handleTogglePassword() {
        showPassword ? setShowPassword(false) : setShowPassword(true)
    }

    const toast = useToast()
    const {signUp} = useAuth()
    async function handleCreateAccountSubmit({
                                                 username,
                                                 email,
                                                 phone,
                                                 password,
                                             }: FieldValues) {
        setIsSubmitting(true)
        try {
            await signUp(username, email, password, phone)
            toast.show({
                title: "Account creation Successful",
                placement: 'top',
                bgColor: THEME.colors.Secondary[500],
            })
        } catch (error) {
            console.log("Error: ", error);
            toast.show({
                title: "Invalid credentials",
                placement: 'top',
                bgColor: THEME.colors.Danger[500],
            })
        } finally {
            setIsSubmitting(false)
        }
    }

    function handleSignInPress() {
        navigation.navigate('signIn')
    }

    // @ts-ignore
    return (
        <SafeAreaView>
            <ScrollView
                contentContainerStyle={{flexGrow: 1}}
                showsVerticalScrollIndicator={false}
            >
                <VStack flex={1} px={'24px'} pt={'32px'} pb={'28px'}>
                    <Center>
                        <ResturantLogo width={24} height={24}/>
                        <Text
                            fontFamily={THEME.Fonts.heading}
                            color={THEME.colors.Primary[700]}
                            fontSize={THEME.FontSizes.xl}
                            mt={'8%'}
                            mb={'2%'}
                        >
                            Create an account
                        </Text>
                    </Center>

                    <Center mt={'10px'} style={{gap: 18}}>
                       <Controller
                            control={control}
                            name="username"
                            render={({field: {onChange, value}}) => (
                                <Input
                                    placeholder="Enter Your Username"
                                    bgColor={THEME.colors.Primary[50]}
                                    borderRadius="6px"
                                    borderWidth={'1px'}
                                    borderColor={THEME.colors.Primary[200]}
                                    paddingX={'12px'}
                                    paddingY={'16px'}
                                    fontSize={THEME.FontSizes.md}
                                    onChangeText={onChange}
                                    value={value}
                                />
                            )}
                        />

                        <ErrorMessage
                            errors={errors}
                            name="username"
                            render={({message}) => (
                                <Text color={THEME.colors.Danger[500]} fontFamily={THEME.Fonts.heading}
                                      style={{marginTop: -15}}>
                                    {message}
                                </Text>
                            )}
                        />

                        <Controller
                            control={control}
                            name="email"
                            render={({field: {onChange, value}}) => (
                                <Input
                                    placeholder="Enter Your Email"
                                    keyboardType="email-address"
                                    autoCapitalize="none"
                                    borderColor={THEME.colors.Primary[200]}
                                    bgColor={THEME.colors.Primary[50]}
                                    borderRadius="6px"
                                    borderWidth={'1px'}
                                    paddingX={'12px'}
                                    paddingY={'16px'}
                                    fontSize={THEME.FontSizes.md}
                                    onChangeText={onChange}
                                    value={value}
                                />
                            )}
                        />

                        <ErrorMessage
                            errors={errors}
                            name="email"
                            render={({message}) => (
                                <Text color={THEME.colors.Danger[500]} fontFamily={THEME.Fonts.heading}
                                      style={{marginTop: -15}}>
                                    {message}
                                </Text>
                            )}
                        />

                        <Controller
                            control={control}
                            name="phone"
                            render={({field: {onChange, value}}) => (
                                <Input
                                    placeholder="Enter Your Phone Number"
                                    keyboardType="phone-pad"
                                    autoCapitalize="none"
                                    borderColor={THEME.colors.Primary[200]}
                                    type="text"
                                    bgColor={THEME.colors.Primary[50]}
                                    borderRadius="6px"
                                    borderWidth={'1px'}
                                    paddingX={'12px'}
                                    paddingY={'16px'}
                                    fontSize={THEME.FontSizes.md}
                                    onChangeText={onChange}
                                    value={value}
                                />
                            )}
                        />

                        <ErrorMessage
                            errors={errors}
                            name="phone"
                            render={({message}) => (
                                <Text color={THEME.colors.Danger[500]} fontFamily={THEME.Fonts.heading}
                                      style={{marginTop: -15}}>
                                    {message}
                                </Text>
                            )}
                        />

                        <Controller
                            control={control}
                            name="password"
                            render={({field: {onChange, value}}) => (
                                <Input
                                    placeholder="Enter Your Password"
                                    type={showPassword ? 'text' : 'password'}
                                    bgColor={THEME.colors.Primary[50]}
                                    borderRadius="6px"
                                    borderWidth={'1px'}
                                    borderColor={THEME.colors.Primary[200]}
                                    paddingX={'12px'}
                                    paddingY={'16px'}
                                    fontSize={THEME.FontSizes.md}
                                    onChangeText={onChange}
                                    value={value}
                                    InputRightElement={
                                        <Button bgColor={THEME.colors.Primary[50]} onPress={handleTogglePassword}>
                                            {
                                                showPassword ?
                                                    <Eye
                                                        style={{width: 20, height: 20}}
                                                        color={THEME.colors.Primary[300]}
                                                    /> :
                                                    <EyeSlash
                                                        style={{width: 20, height: 20}}
                                                        color={THEME.colors.Primary[300]}
                                                    />
                                            }
                                        </Button>
                                    }
                                />
                            )}
                        />

                        <ErrorMessage
                            errors={errors}
                            name="password"
                            render={({message}) => (
                                <Text color={THEME.colors.Danger[500]} fontFamily={THEME.Fonts.heading}
                                      style={{marginTop: -15}}>
                                    {message}
                                </Text>
                            )}
                        />

                    </Center>

                    <ButtonToken
                        message="Sign Up"
                        isLoading={isSubmitting}
                        onPress={handleSubmit(handleCreateAccountSubmit)}
                        mt={'24px'}
                        variant={"GREEN"}
                    />

                    <Center>
                        <Box px={'10px'} mt={''} mb={'5%'}>

                            <HStack width={'90%'} justifyContent={'space-between'} alignItems={'center'}>
                                <Divider width={'30%'} height={'1.5px'}/>
                                <Text color={THEME.colors.Primary[400]} ml={3} mr={3}>or continue with</Text>
                                <Divider width={'30%'} height={'1.5px'}/>
                            </HStack>

                        </Box>
                    </Center>
                    <Box px={'48px'} mb={'5%'}>
                        <Button
                            mt={'20px'}
                            borderRadius={'6px'}
                            borderWidth={'1px'}
                            borderColor={THEME.colors.Primary[300]}
                            fontSize={THEME.FontSizes.sm}
                            width={'100%'}
                            backgroundColor={THEME.colors.Primary[100]}
                            _text={{color: THEME.colors.Primary[300], fontSize: THEME.FontSizes.md}}
                        >

                            <HStack width={'98%'}>
                                <VStack mt={'1px'} marginRight={'10px'}>
                                    <Image
                                        source={GooglLogo}
                                        width={'30px'}
                                        height={'30px'}
                                        borderWidth={5}
                                        alt="Google Logo"
                                    />
                                </VStack>
                                <VStack mt={'1px'} marginRight={'1px'} marginLeft={'1px'}>
                                    <Text color={THEME.colors.Primary[400]} fontSize={THEME.FontSizes.md}>Login with
                                        Google</Text>
                                </VStack>
                            </HStack>
                        </Button>
                        <Center>
                            <HStack mt={'20px'} width={'98%'} alignItems={'center'} justifyContent={'center'}>
                                <VStack mt={'1%'} marginRight={'1%'} marginLeft={'1%'}>
                                    <Text color={THEME.colors.Primary[400]} fontSize={THEME.FontSizes.sm}>Already have an
                                        account?</Text>
                                </VStack>

                                <TouchableOpacity
                                    onPress={handleSignInPress}
                                >
                                    <Text fontFamily={THEME.Fonts.body} fontSize={THEME.FontSizes.sm} marginTop={'3px'}
                                          marginLeft={'5px'}
                                          color={'blue.500'}>SignIn</Text>
                                </TouchableOpacity>
                            </HStack>
                        </Center>
                    </Box>
                </VStack>
            </ScrollView>
        </SafeAreaView>
    )
}
