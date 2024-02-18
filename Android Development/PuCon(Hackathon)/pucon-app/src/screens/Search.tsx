import {Box, HStack, Image, Input, Pressable, ScrollView, Text, VStack} from "native-base";
import React, {useEffect, useState} from "react";
import {addDoc, collection, doc, onSnapshot, setDoc} from "firebase/firestore";
import {FIRESTORE_DB} from "../../firebaseConfig";
import {addRestaurants, addProducts} from "../common/Helpers";
import {THEME} from "../theme";
import {List, MagnifyingGlass, Microphone} from "phosphor-react-native";
import {ButtonToken} from "../components/ButtonToken";
import {Resturant} from "../components/Resturant";
import {RestaurantDTO} from "../dto/restaurantDTO";
import {ResturantComponent} from "../components/ResturantComponent";
import {useNavigation} from "@react-navigation/native";
import {BottomNavigatorRoutesProps} from "../navigation/bottom.routes";
import {ProductDTO} from "../dto/productDTO";
import {LargeLogo} from "../components/LargeLogo";
import User from "../assets/user.png";
import {DrawerNavigatorRoutesProps} from "../navigation/app.routes";

export function Search() {
    const [isLoading, setIsLoading] = useState(false)
    const [restaurants, setRestaurants] = useState<RestaurantDTO[]>([])
    useEffect(() => {
        extractData();
    }, []);

    async function extractData() {
        setIsLoading(true);
        try {
            const restRef = collection(FIRESTORE_DB, 'restaurant');
            const subscriberRest = onSnapshot(restRef, {
                next: (snapshot) => {
                    const rests: any[] = [];

                    snapshot.docs.forEach((doc) => {
                        rests.push({
                            ...doc.data()
                        });
                    })
                    setRestaurants(rests);
                },
            })
        } catch (error) {
            console.log("Error: ", error)
        } finally {
            setIsLoading(false);
        }
    }

    const bottomNav = useNavigation<BottomNavigatorRoutesProps>()
    function handleRestaurantPress(restaurant: RestaurantDTO) {
        bottomNav.navigate('restaurantDetails', restaurant)
    }
    const navigation = useNavigation<DrawerNavigatorRoutesProps>()

    return (<>
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
        <ScrollView>
            <Box
                p={10}
                px={'25px'}
                bgColor={THEME.colors.Primary[50]}
                mt={10}
            >
                <Text fontFamily={THEME.Fonts.heading} fontSize={20}>Find a Restaurant Nearby</Text>

                <Input marginTop={'10px'} backgroundColor={'white'} placeholder=" Search for Restaurant"
                       width="100%" borderRadius="4" py="3" px="1"
                       fontSize="14"
                       InputLeftElement={<MagnifyingGlass style={{marginLeft: 10}}/>}
                       InputRightElement={<Microphone style={{marginRight: 10}}/>}/>
                <ButtonToken
                    message="Search"
                    onPress={() => {
                    }}
                    variant={'GREEN'}
                    width={'100%'}
                    flex={1}
                    marginTop={"20px"}
                    fontSize={THEME.FontSizes.md}
                    _text={{fontSize: THEME.FontSizes.md}}
                />
            </Box>
            <Box
                borderBottomRadius={24}
                pb={'10px'}
                px={'25px'}
            >
                <VStack>
                    <HStack justifyContent={'space-between'} marginTop={'30px'}>
                        <Text fontFamily={THEME.Fonts.heading} fontSize={18}>Popular Restaurants</Text>
                        <Text fontFamily={THEME.Fonts.heading} marginTop={'10px'} color={THEME.colors.Primary[200]}
                              fontSize={15}>7
                            Results</Text>
                    </HStack>
                </VStack>
            </Box>
            {
                restaurants.map((restaurant) => (
                    <Pressable key={restaurant.name} onPress={() => handleRestaurantPress(restaurant)}>
                        <Resturant userName={restaurant.name} locationI={"Lahore, Pakistan"}
                                   reviewText={"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor consectetur adipiscing elit"}
                                   rating={Math.round(restaurant.rating)}/>
                    </Pressable>
                ))
            }
        </ScrollView>
        </>
    )
        ;
}