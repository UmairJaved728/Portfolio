import {Center, Image, View} from 'native-base'
// import Logo from "@assets/logo_1.png";
import React from "react";
import Loader from 'react-native-three-dots'

export function Loading() {
    return (
        <Center style={{flex: 1}}>
        {/*//     <Image*/}
        {/*//         style={{width: 100, height: 50}}*/}
        {/*//         source={Logo}*/}
        {/*//         alt={'App Logo'}*/}
        {/*//         resizeMode={"contain"}*/}
        {/*//         marginBottom={5}*/}
        {/*//     />*/}
            <Loader type="threedots" speed={100} color={'black'}/>
        </Center>
    )
}
