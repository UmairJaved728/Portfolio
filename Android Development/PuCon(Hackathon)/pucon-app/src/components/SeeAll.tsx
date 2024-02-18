import {HStack, Image, Text} from "native-base";
import Logo from '../assets/resturantLogo.png'
import ARestro from "../assets/ARestro.png";
import React from "react";
import {ResturantLogo} from "./ResturantLogo";
import {THEME} from "../theme";
import {CaretRight} from "phosphor-react-native";
export function SeeAll() {
    return (
        <HStack alignItems={'center'}>
            <Text color={THEME.colors.Secondary[500]} fontFamily={THEME.Fonts.body} fontSize={THEME.FontSizes.xs}>See all</Text>
            <CaretRight color={THEME.colors.Secondary[500]}/>
        </HStack>
    )
}
