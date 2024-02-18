import {doc, setDoc} from "firebase/firestore";
import {FIRESTORE_DB} from "../../firebaseConfig";

export async function addRestaurants() {
    await setDoc(doc(FIRESTORE_DB, `restaurant/KFC`), {
        name: "KFC",
        description: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi",
        rating: 4.2,
        facilities: ["Snack bar", "Toilet", "Parking", "24/7"],
        location: {latitude: 31.5204, longitude: 74.3587}
    })
    await setDoc(doc(FIRESTORE_DB, 'restaurant/McDonalds'), {
        name: "McDonalds",
        description: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi",
        rating: 4.4,
        facilities: ["Snack bar", "Toilet", "Parking", "24/7"],
        location: {latitude: 31.5204, longitude: 74.3587}
    })
    await setDoc(doc(FIRESTORE_DB, 'restaurant/Cheezios'), {
        name: "Cheezios",
        description: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi",
        rating: 4.1,
        facilities: ["Snack bar", "Toilet", "Parking", "24/7"],
        location: {latitude: 31.5204, longitude: 74.3587}
    })
    await setDoc(doc(FIRESTORE_DB, 'restaurant/Second Cup'), {
        name: "Second Cup",
        description: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi",
        rating: 2.9,
        facilities: ["Snack bar", "Toilet", "Parking", "24/7"],
        location: {latitude: 31.5204, longitude: 74.3587}
    })
    await setDoc(doc(FIRESTORE_DB, 'restaurant/OPTP'), {
        name: "OPTP",
        description: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi",
        rating: 4.8,
        facilities: ["Snack bar", "Toilet", "Parking", "24/7"],
        location: {latitude: 31.5204, longitude: 74.3587}
    })
    await setDoc(doc(FIRESTORE_DB, 'restaurant/What\'a Paratha'), {
        name: "What\'a Paratha",
        description: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi",
        rating: 3.2,
        facilities: ["Snack bar", "Toilet", "Parking", "24/7"],
        location: {latitude: 31.5204, longitude: 74.3587}
    })
    await setDoc(doc(FIRESTORE_DB, 'restaurant/Timmys'), {
        name: "Timmys",
        description: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi",
        rating: 4.4,
        facilities: ["Snack bar", "Toilet", "Parking", "24/7"],
        location: {latitude: 31.5204, longitude: 74.3587}
    })
    console.log("Items Added")
}

export function getID() {
    return Math.random().toString(36).substring(2,7);
}

export async function addProducts() {

    await setDoc(doc(FIRESTORE_DB, `product/${getID()}`), {
        title: "Pizza",
        description: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi",
        orders: 1020,
        picture: 4,
        price: 899,
        restaurant: "Cheezios"
    });

    await setDoc(doc(FIRESTORE_DB, `product/${getID()}`), {
        title: "Salmon",
        description: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi",
        orders: 32,
        picture: 1,
        price: 1899,
        restaurant: "Timmys"
    });

    await setDoc(doc(FIRESTORE_DB, `product/${getID()}`), {
        title: "Steak",
        description: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi",
        orders: 322,
        picture: 2,
        price: 999,
        restaurant: "KFC"
    });

    await setDoc(doc(FIRESTORE_DB, `product/${getID()}`), {
        title: "Salad",
        description: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi",
        orders: 1322,
        picture: 3,
        price: 1299,
        restaurant: "McDonalds"
    });

    await setDoc(doc(FIRESTORE_DB, `product/${getID()}`), {
        title: "Beef Steak",
        description: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi",
        orders: 611,
        picture: 5,
        price: 1699,
        restaurant: "Second Cup"
    });

    await setDoc(doc(FIRESTORE_DB, `product/${getID()}`), {
        title: "Fried Egg",
        description: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi",
        orders: 811,
        picture: 6,
        price: 1699,
        restaurant: "OPTP"
    });

    await setDoc(doc(FIRESTORE_DB, `product/${getID()}`), {
        title: "Rare Salmon",
        description: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi",
        orders: 111,
        picture: 7,
        price: 999,
        restaurant: "What\'a Paratha"
    });

    await setDoc(doc(FIRESTORE_DB, `product/${getID()}`), {
        title: "Noodles",
        description: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi",
        orders: 111,
        picture: 7,
        price: 999,
        restaurant: "What\'a Paratha"
    });
}
