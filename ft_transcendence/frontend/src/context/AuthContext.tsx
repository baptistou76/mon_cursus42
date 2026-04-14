import { createContext, useContext, useEffect, useState } from "react";

type User = {
  id: number;
  login: string;
  email: string;
  display_name: string;
  avatar: string;
  first_name?: string;
  last_name?: string;
};

type AuthContextType = {
  user: User | null;
  isAuthenticated: boolean;
  loading: boolean;
  login: () => void;
  logout: () => void;
  refreshAuth: () => void;
  localLogin: (email: string, password: string) => Promise<void>;
  localRegister: (
    email: string,
    password: string,
    displayName: string,
    firstName?: string,
    lastName?: string,
  ) => Promise<void>;
};

const AuthContext = createContext<AuthContextType>({
  user: null,
  isAuthenticated: false,
  loading: false,
  refreshAuth: () => {},
  login: () => {},
  logout: () => {},
  localLogin: async () => {},
  localRegister: async () => {},
});

export function AuthProvider({ children }: { children: React.ReactNode }) {
  const [user, setUser] = useState<User | null>(null);
  const [isAuthenticated, setIsAuthenticated] = useState(false);
  const [loading, setLoading] = useState(true);
  const API_URL = (import.meta as any).env?.VITE_API_URL || '/api';

  const refreshAuth = () => {
    fetch(`${API_URL}/me`, {
      credentials: "include",
    })
      .then((res) => {
        if (res.ok) return res.json();

        if (res.status === 401) {
          throw new Error("UNAUTHENTICATED");
        }

        throw new Error(`HTTP ${res.status}: ${res.statusText}`);
      })
      .then((data) => {
        console.log("User data received:", data);
        setUser(data);
        setIsAuthenticated(!!data);
        setLoading(false);
      })
      .catch((error) => {
        if (error.message !== "UNAUTHENTICATED") {
          console.error("Unexpected auth error:", error);
        }

        setUser(null);
        setIsAuthenticated(false);
        setLoading(false);
      });
  };

  useEffect(() => {
    setLoading(true);
    refreshAuth();
  }, []);

  const login = () => {
    window.location.href = `${API_URL}/login42`;
  };

  const logout = () => {
    fetch(`${API_URL}/logout`, {
      method: "POST",
      credentials: "include",
    }).then(() => {
      refreshAuth();
    });
  };

  const localLogin = async (email: string, password: string): Promise<void> => {
    const response = await fetch(`${API_URL}/auth/local/login`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      credentials: "include",
      body: JSON.stringify({ email, password }),
    });

    if (!response.ok) {
      const errorData = await response.json();
      throw new Error(errorData.error || "Login failed");
    }

    refreshAuth();
  };

  const localRegister = async (
    email: string,
    password: string,
    displayName: string,
    firstName?: string,
    lastName?: string,
  ): Promise<void> => {
    const response = await fetch(`${API_URL}/auth/local/register`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      credentials: "include",
      body: JSON.stringify({
        email,
        password,
        display_name: displayName,
        first_name: firstName,
        last_name: lastName,
      }),
    });

    if (!response.ok) {
      const errorData = await response.json();
      throw new Error(errorData.error || "Registration failed");
    }

    refreshAuth();
  };

  return (
    <AuthContext.Provider
      value={{
        user,
        isAuthenticated,
        loading,
        login,
        logout,
        localLogin,
        localRegister,
        refreshAuth,
      }}
    >
      {children}
    </AuthContext.Provider>
  );
}

export function useAuth() {
  const context = useContext(AuthContext);
  if (!context) throw new Error("useAuth must be used within AuthProvider");
  return context;
}
