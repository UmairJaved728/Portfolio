import {useEffect, useState} from 'react'
import {
    Text,
    ScrollView,
    VStack,
    Image,
    Box,
    Input,
    HStack, Pressable, Button, IconButton, View
} from "native-base";
import React from "react";
import {SafeAreaView} from "react-native-safe-area-context";
import {THEME} from "../theme";
import {MapPin, CheckCircle, Microphone, Star, List} from 'phosphor-react-native'
import 'react-native-gesture-handler';
import {useNavigation, useRoute} from "@react-navigation/native";
import {DrawerNavigatorRoutesProps} from "../navigation/app.routes";
import {Maps} from "../components/Maps";
import {ButtonToken} from "../components/ButtonToken";
import {RestaurantDTO} from "../dto/restaurantDTO";
import {Resturant} from "../components/Resturant";
import {One} from "../components/One";
import {ProductDTO} from "../dto/productDTO";
import {collection, onSnapshot} from "firebase/firestore";
import {FIRESTORE_DB} from "../../firebaseConfig";
import {FoodComponent} from "../components/FoodComponent";
import {BottomNavigatorRoutesProps} from "../navigation/bottom.routes";
import {SeeAll} from "../components/SeeAll";
import {LargeLogo} from "../components/LargeLogo";
import User from "../assets/user.png";

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
export function RestaurantDetails() {
    const route = useRoute()
    const restaurant = route.params as RestaurantDTO

    const [isLoading, setIsLoading] = useState(false)
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
                        if(doc.data().restaurant == restaurant.name) {
                            prods.push({
                                id: doc.id,
                                ...doc.data()
                            });
                        }
                    })
                    setProducts(prods);
                },
            })

        } catch (error) {
            console.log("Error: ", error)
        } finally {
            setIsLoading(false);
        }
    }

    const bottomNav = useNavigation<BottomNavigatorRoutesProps>()

    function handleFoodItemPress(food: ProductDTO) {
        bottomNav.navigate('foodOrder', food);
    }

    const navigation = useNavigation<DrawerNavigatorRoutesProps>()
    return (
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
                <VStack>
                    <Image
                        source={require("../assets/resturant.png")}
                        height={'310px'}
                        width={"full"}
                        alt="Product Image"
                        alignSelf={'center'}
                    />
                    <Box
                        borderBottomRadius={24}
                        pb={'10px'}
                        px={'25px'}
                        bgColor={THEME.colors.Primary[100]}
                    >
                        <HStack>
                            <HStack marginLeft={2}>
                                <VStack>
                                    <Text fontFamily={THEME.Fonts.heading} fontSize={25}
                                    >{restaurant.name}</Text>

                                    <Text style={{fontFamily: THEME.Fonts.subHeading, color: THEME.colors.Secondary[500]}}>
                                        Lahore, Pakistan
                                    </Text>
                                    <Text fontFamily={THEME.Fonts.heading} fontSize={THEME.FontSizes.lg}
                                          marginTop={'20px'}>Description</Text>
                                    <Text fontFamily={THEME.Fonts.body} fontSize={THEME.FontSizes.md}
                                          marginTop={'10px'}>{restaurant.description}</Text>
                                </VStack>
                                <View style={{
                                    flexDirection: 'row',
                                    marginLeft: 'auto',
                                    marginTop: '3%',
                                    marginRight: '5%'
                                }}>{renderStars(restaurant.rating)}</View>
                            </HStack>
                        </HStack>
                        <HStack justifyContent={'space-between'} marginTop={'20px'}>
                            <Text fontFamily={THEME.Fonts.heading} fontSize={25}>Best Offers</Text>
                            <SeeAll/>
                        </HStack>
                        <ScrollView
                            horizontal
                            showsHorizontalScrollIndicator={false}
                            contentContainerStyle={{}} // Adjust padding as needed
                        >
                            {
                                products.map((prod) => (
                                    <Pressable onPress={() => handleFoodItemPress(prod)}>
                                        <FoodComponent key={prod.id} product={prod}/>
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
