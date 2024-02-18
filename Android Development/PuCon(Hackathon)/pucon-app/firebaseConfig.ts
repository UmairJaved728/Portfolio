import {initializeApp} from 'firebase/app';
import {getAuth} from 'firebase/auth';
import {getFirestore} from 'firebase/firestore'

const firebaseConfig = {
    apiKey: "AIzaSyBqp37jxYdfAOmzTtpA_HhZ1KuMmbuXnCI",
    authDomain: "pucon-app.firebaseapp.com",
    projectId: "pucon-app",
    storageBucket: "pucon-app.appspot.com",
    messagingSenderId: "34208576478",
    appId: "1:34208576478:web:c0348fb041a152b63c634f",
    measurementId: "G-J0VSMNDFV1"
};

export const FIREBASE_APP = initializeApp(firebaseConfig);
export const FIREBASE_AUTH = getAuth(FIREBASE_APP);
export const FIRESTORE_DB = getFirestore(FIREBASE_APP);