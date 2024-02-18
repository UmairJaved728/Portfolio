import React from "react";
import {HStack, Image, Pressable, Text, View, VStack} from "native-base";
import {Star} from "phosphor-react-native";
import DafaultProfilePicture from "@assets/default_profile_picture.png";
import {useNavigation} from "@react-navigation/native";
import {THEME} from "../theme";
import {One} from "./One";
interface ResturantProps {
    userName: string;
    locationI: string;
    reviewText: string;
    rating: number;
}

const renderStars = (rating: number) => {
    const stars = [];

    let i = 0;
    while (i < rating) {
        stars.push(
            <Star style={{marginRight: 3}} size={15}
                  color={'gold'}
                  weight={'fill'}/>
        );
        i++;
    }

    while (i < 5) {
        stars.push(
            <Star style={{marginRight: 3}} size={15}
                  color={'#C7C6C7'}
                  weight={'fill'}/>
        );
        i++;
    }

    return stars;
};

export function Resturant({userName, locationI, reviewText, rating}: ResturantProps) {

    return (
        <View key={userName} style={{flex: 1, alignItems: 'center', marginBottom: '3%'}}>
            <View backgroundColor={THEME.colors.Primary[50]} width={'94%'} borderRadius={5}>
                <HStack paddingTop={'10px'} marginLeft={2}>
                    <Pressable>
                        <One
                            source={require("../assets/resturant.png")}
                            alt="Picture"
                            size={100}
                        />
                    </Pressable>
                    <VStack marginLeft={'10px'}>
                        {/*<Pressable onPress={handleOpenProfile}>*/}
                            <Text
                                style={{
                                    fontSize: THEME.FontSizes.sm,
                                    marginTop: 3,
                                    marginBottom: 1,
                                    marginLeft: 3,
                                    fontWeight: 'bold',
                                }}
                            >
                                {userName}
                            </Text>
                        {/*</Pressable>*/}

                        <Text style={{fontFamily: THEME.Fonts.subHeading, color: THEME.colors.Secondary[500]}}>
                            {locationI}
                        </Text>
                        <Text
                            style={{
                                fontFamily: THEME.Fonts.body,
                                fontSize: THEME.FontSizes.xs,
                                marginLeft: 6,
                                marginTop: '1%',
                                marginBottom: '5%',
                                width: 200
                            }}
                        >
                            {reviewText}
                        </Text>
                    </VStack>
                    <View style={{
                        flexDirection: 'row',
                        marginLeft: 'auto',
                        marginTop: '2%',
                        marginRight: '5%'
                    }}>{renderStars(rating)}</View>
                </HStack>
            </View>
        </View>
    );
};