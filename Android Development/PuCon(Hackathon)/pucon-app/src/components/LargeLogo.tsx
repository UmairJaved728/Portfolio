import {HStack, Image} from "native-base";
import Logo from '../assets/resturantLogo.png'
import ARestro from "../assets/ARestro.png";
import React from "react";
import {ResturantLogo} from "./ResturantLogo";
import {useNavigation} from "@react-navigation/native";
import {DrawerNavigatorRoutesProps} from "../navigation/app.routes";
export function LargeLogo() {
    const navigation = useNavigation<DrawerNavigatorRoutesProps>()
    return (
        <HStack alignItems={'center'}>
            <ResturantLogo width={8} height={8}/>
            <Image
                source={ARestro}
                width={'105px'}
                height={'20px'}
                borderWidth={5}
                alt="logo"
                marginLeft={'8px'}
            />
        </HStack>
    )
}
