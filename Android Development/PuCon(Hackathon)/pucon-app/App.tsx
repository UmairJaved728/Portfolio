import {StatusBar} from 'expo-status-bar';
import {
    useFonts,
    Karla_400Regular,
    Karla_700Bold,
    Karla_200ExtraLight,
    Karla_300Light,
    Karla_500Medium,
    Karla_600SemiBold,
    Karla_800ExtraBold,
    Karla_300Light_Italic,
    Karla_200ExtraLight_Italic,
    Karla_400Regular_Italic,
    Karla_500Medium_Italic,
    Karla_600SemiBold_Italic, Karla_700Bold_Italic, Karla_800ExtraBold_Italic,
} from '@expo-google-fonts/karla'
import {SafeAreaView} from "react-native-safe-area-context";
import {NativeBaseProvider} from 'native-base'

import {THEME} from './src/theme'
import {Routes} from "./src/navigation";
import React from "react";
import {AuthContextProvider} from "./src/context/AuthContext";

export default function App() {

    const [fontsLoaded] = useFonts({
        Karla_200ExtraLight,
        Karla_300Light,
        Karla_400Regular,
        Karla_500Medium,
        Karla_600SemiBold,
        Karla_700Bold,
        Karla_800ExtraBold,
        Karla_200ExtraLight_Italic,
        Karla_300Light_Italic,
        Karla_400Regular_Italic,
        Karla_500Medium_Italic,
        Karla_600SemiBold_Italic,
        Karla_700Bold_Italic,
        Karla_800ExtraBold_Italic
    })

    return (
        <NativeBaseProvider theme={THEME}>
            <AuthContextProvider>
                <SafeAreaView style={{flex: 1}}>
                    <StatusBar style="auto"/>
                    <Routes/>
                </SafeAreaView>
            </AuthContextProvider>
        </NativeBaseProvider>
    );
}
