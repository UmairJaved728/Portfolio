import {useState} from 'react'
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
import 'react-native-gesture-handler';
import {Resturant} from "../components/Resturant";
import {MagnifyingGlass, Microphone} from "phosphor-react-native";
import {ButtonToken} from "../components/ButtonToken";

export function AllRounder() {
    return (
        <SafeAreaView style={{flex: 1}}>
            <ScrollView
                contentContainerStyle={{flexGrow: 1}}
                showsVerticalScrollIndicator={false}
            ><Box
                borderBottomRadius={24}
                pb={'10px'}
                px={'25px'}
                bgColor={THEME.colors.Primary[100]}
            >
                <Text fontFamily={THEME.Fonts.heading} fontSize={20}>Find a Restaurant Nearby</Text>

                <Input marginTop={'10px'} backgroundColor={'white'} placeholder=" Search for Restaurant"
                       width="100%" borderRadius="4" py="3" px="1"
                       fontSize="14"
                       InputLeftElement={<MagnifyingGlass style={{marginLeft: 10}}/>}
                       InputRightElement={<Microphone style={{marginRight: 10}}/>}/>
                <ButtonToken
                    message="Search"
                    onPress={()=>{}}
                    variant={'GREEN'}
                    width={'100%'}
                    flex={1}
                    marginTop={"20px"}
                    fontSize={THEME.FontSizes.md}
                    _text={{fontSize: THEME.FontSizes.md}}
                />
                <VStack>
                    <HStack justifyContent={'space-between'} marginTop={'30px'}>
                        <Text fontFamily={THEME.Fonts.heading} fontSize={25}>Popular Restaurants</Text>
                        <Text fontFamily={THEME.Fonts.heading} marginTop={'10px'} color={THEME.colors.Primary[200]} fontSize={15}>10
                            Results</Text>
                    </HStack>
                </VStack>
            </Box>
                <Resturant userName={"Resturant Name"} locationI={"Location"}
                           reviewText={"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor consectetur adipiscing elit"}
                           rating={4}/>
            </ScrollView>
        </SafeAreaView>
    )
}
