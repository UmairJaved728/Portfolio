import {
    createNativeStackNavigator,
    NativeStackNavigationProp,
} from '@react-navigation/native-stack'

// import {Signup} from '../screens/Signup'
import {SplashScreen} from "../screens/SplashScreen";
import {Signup} from '../screens/Signup'
import {AllRounder} from '../screens/AllRounder'
import {SignIn} from "../screens/SignIn";
import {ForgotPassword} from "../screens/ForgotPassword";

type TAuthRoutes = {
    allRounder: undefined
    signUp: undefined
    splash: undefined
    signIn: undefined
    forgotPassword: undefined
}

export type AuthNavigatorRoutesProps = NativeStackNavigationProp<TAuthRoutes>

const {Navigator, Screen} = createNativeStackNavigator<TAuthRoutes>()

export function AuthRoutes() {
    return (
        <Navigator screenOptions={{headerShown: false}}>
            {/*<Screen name={"allRounder"} component={AllRounder} />*/}
            <Screen name={"splash"} component={SplashScreen} />
            <Screen name={"signIn"} component={SignIn} />
            <Screen name={"forgotPassword"} component={ForgotPassword} />
            <Screen name={"signUp"} component={Signup} />
        </Navigator>
    )
}
