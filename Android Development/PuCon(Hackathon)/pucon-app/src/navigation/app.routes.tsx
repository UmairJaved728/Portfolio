import {createDrawerNavigator, DrawerNavigationProp} from '@react-navigation/drawer';
import {AllRounder} from "../screens/AllRounder";
import {BottomRoutes} from "./bottom.routes";
import {useTheme} from "native-base";
import {Home} from "../screens/Home";
import {Search} from "../screens/Search";

type TAppRoutes = {
    Home: undefined
    Restaurants: undefined
}

export type DrawerNavigatorRoutesProps = DrawerNavigationProp<TAppRoutes>

const {Navigator, Screen} = createDrawerNavigator<TAppRoutes>();

export function AppRoutes() {
    return (
        <Navigator screenOptions={{
           headerShown: false
        }}>
            <Screen name="Home" component={BottomRoutes}/>
            <Screen name="Restaurants" component={Search}/>
        </Navigator>
    );
}
