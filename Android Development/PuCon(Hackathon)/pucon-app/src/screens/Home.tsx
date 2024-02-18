import {useEffect, useState} from 'react'
import {
    Text,
    ScrollView,
    VStack,
    Image,
    Box,
    Input,
    HStack, Pressable
} from "native-base";
import React from "react";
import {SafeAreaView} from "react-native-safe-area-context";
import {THEME} from "../theme";
import {List, MagnifyingGlass, Microphone, Star} from 'phosphor-react-native'
import 'react-native-gesture-handler';
import User from "../assets/user.png";
import {LargeLogo} from "../components/LargeLogo";
import ResturantHeader from "../assets/resturantHeader.png";
import {SeeAll} from "../components/SeeAll";
import {useNavigation} from "@react-navigation/native";
import {DrawerNavigatorRoutesProps} from "../navigation/app.routes";
import {FoodComponent} from "../components/FoodComponent";
import {ResturantComponent} from "../components/ResturantComponent";
import {RestaurantDTO} from "../dto/restaurantDTO";
import {ProductDTO} from "../dto/productDTO";
import {collection, onSnapshot} from "firebase/firestore";
import {FIRESTORE_DB} from "../../firebaseConfig";
import {Loading} from "../components/Loading";
import {BottomTabNavigationProp} from "@react-navigation/bottom-tabs";
import {BottomNavigatorRoutesProps} from "../navigation/bottom.routes";

export function Home() {
    const [isLoading, setIsLoading] = useState(false)
    const [restaurants, setRestaurants] = useState<RestaurantDTO[]>([])
    const [products, setProducts] = useState<ProductDTO[]>([])


    useEffect(() => {
        extractData();
    }, []);

    async function extractData() {
        setIsLoading(true);
        try {

            const prodRef = collection(FIRESTORE_DB, 'product');
            const subscriberProd = onSnapshot(prodRef, {
                next: (snapshot) => {
                    const prods: any[] = []

                    snapshot.docs.forEach((doc) => {
                        prods.push({
                            id: doc.id,
                            ...doc.data()
                        });
                    })
                    setProducts(prods);
                },
            })

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

    const navigation = useNavigation<DrawerNavigatorRoutesProps>()

    const bottomNav = useNavigation<BottomNavigatorRoutesProps>()

    function handleFoodItemPress(food: ProductDTO) {
        bottomNav.navigate('foodOrder', food);
    }

    function handleRestaurantPress(restaurant: RestaurantDTO) {
        bottomNav.navigate('restaurantDetails', restaurant)
    }

    return (
        isLoading ? <Loading/> :
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

                    <VStack flex={1}>
                        <Box
                            borderBottomRadius={24}
                            pb={'10px'}
                            px={'25px'}
                            bgColor={THEME.colors.Primary[100]}
                        >
                            <Box alignSelf={'center'} width={'350px'} mt={'30px'}>
                                <Image
                                    source={ResturantHeader}
                                    height={'150px'}
                                    width={'300px'}
                                    borderRadius={'10px'}
                                    alt="Resturant Header"
                                    alignSelf={'center'}
                                />
                            </Box>
                            <Input marginTop={'20px'} backgroundColor={'white'} placeholder="Search People & Places"
                                   width="100%" borderRadius="4" py="3" px="1"
                                   fontSize="14"
                                   InputLeftElement={<MagnifyingGlass style={{marginLeft: 10}}/>}
                                   InputRightElement={<Microphone style={{marginRight: 10}}/>}/>
                            <HStack justifyContent={'space-between'} marginTop={'10px'}>
                                <Text fontFamily={THEME.Fonts.heading} fontSize={25}>Best Offers</Text>
                                <SeeAll/>
                            </HStack>
                            {/*APply horizontal scrollable*/}
                            <ScrollView
                                horizontal
                                showsHorizontalScrollIndicator={false}
                                contentContainerStyle={{}} // Adjust padding as needed
                            >
                                {
                                    products.map((prod) => (
                                        <Pressable key={prod.id} onPress={() => handleFoodItemPress(prod)}>
                                            <FoodComponent product={prod}/>
                                        </Pressable>
                                    ))
                                }
                            </ScrollView>
                            <Text fontFamily={THEME.Fonts.heading} fontSize={25} marginTop={'10px'}>Resturants
                                NearBy</Text>
                            <ScrollView
                                horizontal
                                showsHorizontalScrollIndicator={false}
                                contentContainerStyle={{}} // Adjust padding as needed
                            >
                                {
                                    restaurants.map((restaurant) => (
                                        <Pressable key={restaurant.name} onPress={() => handleRestaurantPress(restaurant)}>
                                            <ResturantComponent restaurant={restaurant} key={restaurant.name}/>
                                        </Pressable>
                                    ))
                                }
                            </ScrollView>
                        </Box>
                    </VStack>
                </ScrollView>
            </SafeAreaView>
    )
}
