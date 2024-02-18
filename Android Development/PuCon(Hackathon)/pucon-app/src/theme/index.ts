import {extendTheme} from 'native-base'

export const THEME = extendTheme({

    colors: {
        "Secondary": {
            50: "#D9D8DA",
            100: "#82e5aa",
            200: "#67d894",
            300: "#4fc980",
            400: "#39b76b",
            500: "#009944",
            600: "#398858",
            700: "#37724f",
            800: "#345e45",
            900: "#2f4b3a"
        },

        "Danger": {
            50: '#fee2e2',
            100: '#fecaca',
            200: '#fca5a5',
            300: '#EE7979',
            400: '#f87171',
            500: '#ef4444',
            600: '#dc2626',
            700: '#b91c1c',
            800: '#991b1b',
            900: '#7f1d1d',
        },

        "Primary": {
            50: "#FFFFFF",
            100: "#EDECEE",
            150: "#dcdcdc",
            200: "#9F9BA1",
            300: "#5F5B62",
            400: "#3E3A40",
            500: "#D9D8DA",
            600: "#252a2a",
            700: "#1A181B",
            800: "#0d1313",
            900: "#000000"
        },

        "Tertiary": {
            500: 'rgba(79,201,128,0.3)',
            // 600: 'rgba(26,24,27,0.83)', //light black
            600: 'rgba(0,0,0, 0.7)',
        },

        "Gold": {
            100: "#FFB400"
        }
    },

    opacity: {
        0: 0,
        5: 0.05,
        10: 0.1,
        20: 0.2,
        25: 0.25,
        30: 0.3,
        40: 0.4,
        50: 0.5,
        60: 0.6,
        70: 0.7,
        75: 0.75,
        80: 0.8,
        90: 0.9,
        95: 0.95,
        100: 1,
    },

    fontConfig: {
        "Karla": {
            "200": {
                "normal": "Karla_200ExtraLight",
                "italic": "Karla_200ExtraLight_Italic"
            },
            "300": {
                "normal": "Karla_300Light",
                "italic": "Karla_300Light_Italic"
            },
            "400": {
                "normal": "Karla_400Regular",
                "italic": "Karla_400Regular_Italic"
            },
            "500": {
                "normal": "Karla_500Medium",
                "italic": "Karla_500Medium_Italic"
            },
            "600": {
                "normal": "Karla_600SemiBold",
                "italic": "Karla_600SemiBold_Italic"
            },
            "700": {
                "normal": "Karla_700Bold",
                "italic": "Karla_700Bold_Italic"
            },
            "800": {
                "normal": "Karla_800ExtraBold",
                "italic": "Karla_800ExtraBold_Italic"
            }
        },
    },

    Fonts: {
        heading: 'Karla_700Bold',
        subHeading: 'Karla_600SemiBold',
        body: "Karla_400Regular",
    },

    //use: <Text fontFamily="body" fontWeight="600" fontStyle="italic" />

    FontSizes: {
        xxs: 12,
        xs: 14,
        sm: 16,
        md: 18,
        lg: 20,
        xl: 24,
        xxl: 28,
    },
});
