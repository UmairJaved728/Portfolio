import {useEffect, useState} from 'react'
import {
    Text,
    ScrollView,
    VStack,
    Image,
    Box,
    Input,
    HStack, Pressable, Button, IconButton
} from "native-base";
import React from "react";
import {SafeAreaView} from "react-native-safe-area-context";
import {THEME} from "../theme";
import {MapPin, CheckCircle, Microphone, Star, List} from 'phosphor-react-native'
import 'react-native-gesture-handler';
import {useNavigation, useRoute} from "@react-navigation/native";
import {DrawerNavigatorRoutesProps} from "../navigation/app.routes";
import {Maps} from "../components/Maps";
import {ButtonToken} from "../components/ButtonToken";
import {ProductDTO} from "../dto/productDTO";
import {LargeLogo} from "../components/LargeLogo";
import User from "../assets/user.png";

export function FoodOrder() {
    const route = useRoute()
    const [pic, setPic] = useState(require("../assets/Food_1.png"))
    const product = route.params as ProductDTO

    const IdToImage = {
        1: require("../assets/Food_1.png"),
        2: require("../assets/Food_2.png"),
        3: require("../assets/Food_3.png"),
        4: require("../assets/Food_4.png"),
        5: require("../assets/Food_5.png"),
        6: require("../assets/Food_6.png"),
        7: require("../assets/Food_7.png"),
        8: require("../assets/Food_8.png"),
        9: require("../assets/Food_9.png"),
    }

    useEffect(() => {
        setPic(IdToImage[product.picture])
        console.log(IdToImage[product.picture])
    }, [product]);

    const navigation = useNavigation<DrawerNavigatorRoutesProps>()
    return (
        <SafeAreaView style={{flex: 1}}>
            <VStack marginTop={'-45px'} backgroundColor={'white'}
                    px={'30px'} pt={'50px'} pb={'10px'}>
                <HStack width={'98%'} justifyContent={'space-between'} alignItems={'center'}>
                    <Pressable onPress={() => navigation.openDrawer()}>
                        <List size={30}/>
                    </Pressable>
                    <LargeLogo/>
                    <Image
                        source={User}
                        height={'40px'}
                        width={'40px'}
                        rounded="full"
                        borderWidth={5}
                        alt="User"
                    />
                </HStack>
            </VStack>
            <ScrollView
                contentContainerStyle={{flexGrow: 1}}
                showsVerticalScrollIndicator={false}
            >
                <VStack>
                    <Box height={'400px'} p={5}>
                        <Image
                            source={pic}
                            height={'310px'}
                            width={"350px"}
                            alt="Product Image"
                            alignSelf={'center'}
                        />
                    </Box>
                    <Box
                        borderBottomRadius={24}
                        pb={'10px'}
                        px={'25px'}
                        bgColor={THEME.colors.Primary[100]}
                    >
                        <HStack justifyContent={'space-between'}>
                            <Button
                                mt={'20px'}
                                width={'100px'}
                                borderRadius={'6px'}
                                fontSize={THEME.FontSizes.sm}
                                backgroundColor={THEME.colors.Primary[100]}
                                _text={{color: THEME.colors.Secondary[500], fontSize: THEME.FontSizes.md}}
                                style={{backgroundColor: THEME.colors.Tertiary[500]}}
                            >
                                Popular
                            </Button>
                            <Maps/>
                        </HStack>
                        <Text fontFamily={THEME.Fonts.heading} fontSize={25} marginTop={'10px'}>{product.title}</Text>
                        <HStack>
                            <HStack marginRight={'50px'}>
                                <Star color={'#FF8610'} weight={'fill'} style={{marginTop: 3}}/>
                                <Text fontFamily={THEME.Fonts.body} color={THEME.colors.Primary[200]} marginLeft={'5px'}
                                      fontSize={20}>4.8</Text>
                            </HStack>

                            <HStack>
                                <CheckCircle color={THEME.colors.Secondary[500]} weight={'fill'}
                                             style={{marginTop: 3}}/>
                                <Text fontFamily={THEME.Fonts.body} color={THEME.colors.Primary[200]} marginLeft={'5px'}
                                      fontSize={20}>{Math.round(product.orders / 100) * 100 + "+ orders"}</Text>
                            </HStack>
                        </HStack>
                        <Text fontFamily={THEME.Fonts.body} fontSize={THEME.FontSizes.lg}
                              marginTop={'10px'}>Description</Text>
                        <Text fontFamily={THEME.Fonts.body} fontSize={THEME.FontSizes.md}
                              marginTop={'10px'}>{product.description}</Text>
                        <ButtonToken
                            message="Add to Cart"
                            onPress={() => {
                            }}
                            variant={'GREEN'}
                            mt={'20px'}
                        />
                    </Box>
                </VStack>
            </ScrollView>
        </SafeAreaView>
    )
}
