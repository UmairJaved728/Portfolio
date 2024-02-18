import {HStack, IconButton, Image} from "native-base";
import Logo from '../assets/resturantLogo.png'
import ARestro from "../assets/ARestro.png";
import React from "react";
import {ResturantLogo} from "./ResturantLogo";
import {useNavigation} from "@react-navigation/native";
import {DrawerNavigatorRoutesProps} from "../navigation/app.routes";
import {Heart, MapPin} from "phosphor-react-native";

export function Maps() {
    return (
        <HStack>
            <IconButton marginTop={'20px'} marginRight={'5px'} borderRadius={'full'} width={'40px'} height={'40px'} colorScheme="gray"
                        key={"outline"} variant={"outline"}
                        style={{backgroundColor: "#DCD5D5", borderColor: "#DCD5D5"}} _icon={{
                as: <MapPin weight={'fill'}/>,
                name: "search1"
            }}/>
            <IconButton marginTop={'20px'} borderRadius={'full'} width={'40px'} height={'40px'} colorScheme="gray"
                        key={"outline1"} variant={"outline"}
                        style={{backgroundColor: "#DCD5D5", borderColor: "#DCD5D5"}} _icon={{
                as: <Heart weight={'fill'}/>,
                name: "search1"
            }}/>
        </HStack>
    )
}
