import {Box, Center, HStack, Image, Text} from "native-base";
import React from "react";
import {THEME} from "../theme";
import Resturant from "../assets/resturant.png";
import {Star} from "phosphor-react-native";
import {RestaurantDTO} from "../dto/restaurantDTO";

interface ResturantComponentProps {
    restaurant: RestaurantDTO
}

export function ResturantComponent({restaurant}: ResturantComponentProps) {
    return (
        <Box margin={'10px'}>
            <Image
                marginTop={'10px'}
                source={Resturant}
                height={'100px'}
                width={'200px'}
                borderRadius={'15px'}
                alt="Resturant"
            />
            <Text fontFamily={THEME.Fonts.subHeading} marginTop={'10px'} fontSize={20}
                  color={THEME.colors.Primary[700]}>{restaurant.name}</Text>
            <HStack>
                <Star color={'#FF8610'} weight={'fill'} style={{marginTop: 3}}/>
                <Text fontFamily={THEME.Fonts.subHeading} marginLeft={'5px'} fontSize={20}>{restaurant.rating}</Text>
            </HStack>
        </Box>
    )
}
