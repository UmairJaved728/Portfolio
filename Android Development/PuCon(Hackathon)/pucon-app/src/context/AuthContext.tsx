import React, {Dispatch, ReactNode, createContext, useEffect, useState, SetStateAction, useContext} from 'react'

import {UserDTO} from '../dto/UserDTO'
import {FIREBASE_AUTH, FIRESTORE_DB} from "../../firebaseConfig";
import {createUserWithEmailAndPassword, signInWithEmailAndPassword, signOut, User, onAuthStateChanged} from 'firebase/auth';
import {collection, addDoc, getFirestore, setDoc, doc, getDoc} from 'firebase/firestore'
import firebase from "firebase/compat";
import firestore = firebase.firestore;
import UserCredential = firebase.auth.UserCredential;
type AuthContextDataProps = {
    user: UserDTO,
    signIn: (email: string, password: string) => void
    signUp: (username: string, email: string, password: string, phone: string) => void
    signOut: () => void
}

type AuthContextProviderProps = {
    children: ReactNode
}

export const AuthContext = createContext<AuthContextDataProps>(
    {} as AuthContextDataProps,
)

export function AuthContextProvider({children}: AuthContextProviderProps) {
    const [authUser, setAuthUser] = useState<User>();
    const [user, setUser] = useState<UserDTO>(undefined)

    async function updateUser(email: string) {
        const docRef = doc(FIRESTORE_DB, `user/${email}`);
       const userDoc = await getDoc(docRef);
       const userData : UserDTO = {
           email: userDoc.data().email,
           phone: userDoc.data().email,
           username: userDoc.data().email,
       }

       setUser(userData);
    }

    useEffect(() => {
        const unsubscribeFromAuthStatuChanged = onAuthStateChanged(FIREBASE_AUTH, (user) => {
            if (user) {
                // User is signed in, see docs for a list of available properties
                // https://firebase.google.com/docs/reference/js/firebase.User
                setAuthUser(user);
                console.log("Auth Changed: ", user);
            } else {
                // User is signed out
                setAuthUser(undefined);
            }
        });

        return unsubscribeFromAuthStatuChanged;
    }, []);

    async function signIn(email: string, password: string) {
        await signInWithEmailAndPassword(FIREBASE_AUTH, email, password);
        await updateUser(email);
    }

    async function signUp(username: string, email: string, password: string, phone: string) {
        const userCredential = await createUserWithEmailAndPassword(FIREBASE_AUTH, email, password);
        await setDoc(doc(FIRESTORE_DB, "user", email), {username: username, email: email, phone: phone, password: password});
        await signInWithEmailAndPassword(FIREBASE_AUTH, email, password);
        await updateUser(email);
    }

    async function signOutUser() {
        signOut(FIREBASE_AUTH);
    }

    return (
        <AuthContext.Provider
            value={{user, signUp, signIn, signOut: signOutUser}}
        >
            {children}
        </AuthContext.Provider>
    )
}

export function useAuth() {
    return useContext(AuthContext)
}
