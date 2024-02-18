import {Box, Center, HStack, Image, Text} from "native-base";
import Logo from '../assets/resturantLogo.png'
import ARestro from "../assets/ARestro.png";
import React from "react";
import {ResturantLogo} from "./ResturantLogo";
import {useNavigation} from "@react-navigation/native";
import {DrawerNavigatorRoutesProps} from "../navigation/app.routes";
import Ima from "../assets/Food_1.png";
import {THEME} from "../theme";
import {ProductDTO} from "../dto/productDTO";

interface FoodComponentProps {
    product: ProductDTO
}
export function FoodComponent({product}: FoodComponentProps) {


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

    return (
        <Box alignItems={'center'} m={5}>
            <Image
                source={IdToImage[product.picture]}
                width={190}
                height={190}
                rounded="full"
                borderWidth={5}
                zIndex={2}
                alt="App Logo"
                marginLeft={'-15px'}
            />
            <Center paddingBottom={'15px'} backgroundColor={'white'} borderRadius={'10px'} width={'150px'} marginTop={'-80px'}>
                <Text marginTop={'100px'} fontFamily={THEME.Fonts.subHeading} fontSize={THEME.FontSizes.sm}>{product.title}</Text>
                <Text fontFamily={THEME.Fonts.body} fontSize={THEME.FontSizes.sm} color={THEME.colors.Primary[200]}>{product.description.substring(0, 15) + "..."}</Text>
                <HStack>
                    <Text fontFamily={THEME.Fonts.body} fontSize={THEME.FontSizes.xs}>Rs</Text>
                    <Text fontFamily={THEME.Fonts.heading} fontSize={THEME.FontSizes.lg}
                          color={THEME.colors.Secondary[500]} marginLeft={'5px'}>{product.price}</Text>
                </HStack>
            </Center>
        </Box>
    )
}
