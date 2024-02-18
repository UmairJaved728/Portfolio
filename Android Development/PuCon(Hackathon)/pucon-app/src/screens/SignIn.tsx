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
    FormControl, useToast
} from "native-base";
import React from "react";
import {SafeAreaView} from "react-native-safe-area-context";
import {THEME} from "../theme";
import {ButtonToken} from "../components/ButtonToken";
import {ResturantLogo} from "../components/ResturantLogo";
import {Eye, EyeSlash} from 'phosphor-react-native'
import {Checkbox} from "../components/Checkbox";
import {TouchableOpacity} from "react-native";
import {Controller, FieldValues, useForm} from 'react-hook-form'
import * as yup from 'yup'
import {yupResolver} from '@hookform/resolvers/yup'
import {ErrorMessage} from '@hookform/error-message'
import GooglLogo from "../assets/iconGoogle.png";
import {useNavigation} from "@react-navigation/native";
import {AuthNavigatorRoutesProps} from "../navigation/auth.routes";
import {useAuth} from "../context/AuthContext";

interface FormDataProps {
    email: string
    password: string
}

const schema = yup.object().shape({
    email: yup.string().required('E-mail cannot be empty').email('Invalid Email!.'),
    password: yup.string().required('Password cannot be empty'),
})


export function SignIn() {
    const navigation = useNavigation<AuthNavigatorRoutesProps>()

    const [showPassword, setShowPassword] = useState(false)
    const [isSubmitting, setIsSubmitting] = useState(false)
    const [remember, setRemember] = useState(true);

    const {
        control,
        handleSubmit,
        formState: {errors},
    } = useForm<FormDataProps>({resolver: yupResolver(schema)})

    const {signIn} = useAuth()

    const toast = useToast();
    async function handleSignIn({email, password}: FieldValues) {
        try {
            setIsSubmitting(true)
            await signIn(email, password)
            toast.show({
                title: "Sign In Successful",
                placement: 'top',
                bgColor: THEME.colors.Secondary[500],
            })
        } catch (error: any) {
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

    function handleCreateAccountPress() {
        navigation.navigate('signUp')
    }

    function handleTogglePassword() {
        showPassword ? setShowPassword(false) : setShowPassword(true)
    }

    function handleToggle() {
        setRemember(!remember);
    }

    function handleForgotPassword() {
        navigation.push('forgotPassword')
    }

    return (
        <SafeAreaView>
            <ScrollView
                contentContainerStyle={{flexGrow: 1}}
                showsVerticalScrollIndicator={false}
            >
                <VStack flex={1}>
                    <Box
                        h={536}
                        borderBottomRadius={24}
                        pt={'68px'}
                        pb={'10px'}
                        px={'48px'}
                        bgColor={THEME.colors.Primary[100]}
                    >
                        <Center>
                            <ResturantLogo width={24} height={24}/>
                            <Text textAlign={'center'} fontFamily={THEME.Fonts.heading}
                                  color={THEME.colors.Primary[300]}
                                  mt={'8%'} fontSize={THEME.FontSizes.xxl}>
                                Log In
                            </Text>
                        </Center>

                        <Box mt={'5%'}>
                            <Text style={{fontWeight: "800"}}>Email</Text>
                            <Controller
                                control={control}
                                name="email"
                                render={({field: {onChange, value}}) => (
                                    <Input
                                        placeholder="example@gmail.com"
                                        keyboardType="email-address"
                                        autoCapitalize="none"
                                        bgColor={THEME.colors.Primary[50]}
                                        borderRadius="6px"
                                        borderColor={THEME.colors.Primary[100]}
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
                                          style={{marginTop: 5}}>
                                        {message}
                                    </Text>
                                )}
                            />
                            <Text style={{fontWeight: "800", marginTop: 20}}>Password</Text>

                            <Controller
                                control={control}
                                name="password"
                                render={({field: {onChange, value}}) => (
                                    <Input
                                        placeholder="Enter Your Password"
                                        type={showPassword ? 'text' : 'password'}
                                        bgColor={THEME.colors.Primary[50]}
                                        borderRadius="6px"
                                        borderColor={THEME.colors.Primary[100]}
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
                                          style={{marginTop: 5}}>
                                        {message}
                                    </Text>
                                )}
                            />

                        </Box>

                        <HStack mt={'20px'} width={'98%'} justifyContent={'space-between'}>
                            <VStack mt={'1%'} marginRight={'1%'} marginLeft={'1%'}>
                                <Checkbox label="Remember me" isChecked={remember} onToggle={handleToggle}/>
                            </VStack>

                            <TouchableOpacity
                                onPress={handleForgotPassword}
                            >
                                <Text fontFamily={THEME.Fonts.body} fontSize={THEME.FontSizes.xs}
                                      color={THEME.colors.error[500]}>Forgot password?</Text>
                            </TouchableOpacity>
                        </HStack>

                        <ButtonToken
                            message="Login"
                            onPress={handleSubmit(handleSignIn)}
                            variant={'GREEN'}
                            mt={'20px'}
                            isLoading={isSubmitting}
                        />

                    </Box>
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
                                    <Text color={THEME.colors.Primary[400]} fontSize={THEME.FontSizes.sm}>Don't have an
                                        account?</Text>
                                </VStack>

                                <TouchableOpacity
                                    onPress={handleCreateAccountPress}
                                >
                                    <Text fontFamily={THEME.Fonts.body} fontSize={THEME.FontSizes.sm} marginTop={'3px'}
                                          marginLeft={'5px'}
                                          color={'blue.500'}>SignUp</Text>
                                </TouchableOpacity>
                            </HStack>
                        </Center>
                    </Box>
                </VStack>
            </ScrollView>
        </SafeAreaView>
    )
}
