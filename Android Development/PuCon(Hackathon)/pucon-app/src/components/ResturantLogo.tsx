import {Image} from "native-base";
import Logo from '../assets/resturantLogo.png'

interface ResturantLogoProps {
    width: number;
    height: number;
}
export function ResturantLogo({width, height}: ResturantLogoProps) {
    return (
        <Image
            source={Logo}
            width={width}
            height={height}
            rounded="full"
            borderWidth={5}
            alt="App Logo"
        />
    )
}
