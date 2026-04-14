import { useTranslation } from "react-i18next";
import React, { useEffect, useState, useRef } from "react";
import { HiCheck, HiExclamation } from "react-icons/hi";
import { useAuth } from "../context/AuthContext";
import {
  Button,
  Label,
  TextInput,
  FileInput,
  Toast,
  ToastToggle,
  Spinner,
} from "flowbite-react";

const API_URL = (import.meta as any).env?.VITE_API_URL || '/api';

type FormShape = {
  displayName: string;
  email: string;
  login: string;
  firstName: string;
  lastName: string;
  avatar?: string;
};

const Settings: React.FC = () => {
  const { user, loading, refreshAuth } = useAuth();
  const [form, setForm] = useState<FormShape>({
    displayName: "",
    email: "",
    login: "",
    firstName: "",
    lastName: "",
    avatar: "",
  });

  // Avatar upload states
  const [avatarFile, setAvatarFile] = useState<File | null>(null);
  const [avatarPreview, setAvatarPreview] = useState<string | null>(null);
  const fileInputRef = useRef<HTMLInputElement>(null);

  const [saving, setSaving] = useState(false);
  const [message, setMessage] = useState<string | null>(null);
  const { t } = useTranslation();

  useEffect(() => {
    if (!user) return;
    setForm({
      displayName: user.display_name ?? "",
      email: user.email ?? "",
      login: user.login ?? "",
      firstName: user.first_name ?? "",
      lastName: user.last_name ?? "",
      avatar: user.avatar ?? "",
    });
    if (user.avatar) {
      setAvatarPreview(user.avatar);
    }
  }, [user]);

  const handleChange = (
    e: React.ChangeEvent<HTMLInputElement | HTMLTextAreaElement>,
  ) => {
    const { name, value } = e.target;
    setForm((prev) => ({ ...prev, [name]: value }));
  };

  const handleAvatarChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    const file = e.target.files?.[0];
    if (!file) return;
    const validTypes = ["image/jpeg", "image/png", "image/gif"];
    if (!validTypes.includes(file.type)) {
      alert("Please select a valid image file (jpg, png, gif).");
      return;
    }
    const maxSize = 5 * 1024 * 1024; // 5MB
    if (file.size > maxSize) {
      alert("File size exceeds 5MB limit.");
      return;
    }
    setAvatarFile(file);

    setAvatarPreview(URL.createObjectURL(file));
    setMessage(null);
  };

  const uploadAvatar = async (): Promise<string | null> => {
    if (!avatarFile) return null;
    const formData = new FormData();
    formData.append("avatar", avatarFile);

    try {
      const res = await fetch(`${API_URL}/me/avatar`, {
        method: "POST",
        credentials: "include",
        body: formData,
      });
      if (!res.ok) {
        const err = await res.json().catch(() => ({}));
        throw new Error(err.error || `HTTP ${res.status}`);
      }
      const data = await res.json();
      return data.avatar;
    } catch (err: any) {
      console.error("Avatar upload error:", err);
      setMessage(`Error uploading avatar: ${err.message ?? err}`);
      return null;
    }
  };

  const updateProfilData = async () => {
    const res = await fetch(`${API_URL}/me`, {
      method: "PATCH",
      headers: { "Content-Type": "application/json" },
      credentials: "include",
      body: JSON.stringify(form),
    });
    if (!res.ok) {
      const err = await res.json().catch(() => ({}));
      throw new Error(err.error || `HTTP ${res.status}`);
    }
  };

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();
    setSaving(true);
    setMessage(null);

    try {
      if (avatarFile) {
        const avatarUrl = await uploadAvatar();
        if (avatarUrl) {
          form.avatar = avatarUrl;
        } else {
          throw new Error("Avatar upload failed.");
        }
      }
      await updateProfilData();
      await refreshAuth();

      setMessage("Data saved successfully!");
      setAvatarFile(null);
    } catch (err: any) {
      console.error("Save profile error:", err);
      setMessage(`Error saving data: ${err.message ?? err}`);
    } finally {
      setSaving(false);
    }
  };

  if (loading)
    return (
      <div className="flex flex-wrap gap-2">
        <Spinner color="purple" aria-label="Loading..." />
      </div>
    );

  return (
    <div className="flex min-h-screen flex-col content-center items-center justify-center px-4 sm:px-6 lg:px-8 py-4 sm:py-6">
      <h2 className="pb-4 text-2xl font-bold">{t("settings.head")}</h2>
      {message && (
        <div className="mb-4">
          <Toast>
            <div className="inline-flex h-8 w-8 shrink-0 items-center justify-center rounded-lg bg-green-100 text-green-500 dark:bg-green-800 dark:text-green-200">
              <HiCheck className="h-5 w-5" />
            </div>
            <div className="ml-3 text-sm font-normal">{message}</div>
            <ToastToggle />
          </Toast>
        </div>
      )}

      {!user && <p>User not found in context. Please log in.</p>}

      {user && (
        <form onSubmit={handleSubmit} className="flex w-full max-w-md flex-col gap-4">
          <div>
            <Label htmlFor="avatar">{t("settings.avatar")}</Label>
            <FileInput
              id="avatar"
              name="avatar"
              onChange={handleAvatarChange}
              accept="image/*"
              ref={fileInputRef}
            />
            {avatarPreview && (
              <img
                src={avatarPreview}
                alt="Avatar Preview"
                className="mt-2 h-24 w-24 sm:h-32 sm:w-32 rounded-full border object-cover"
              />
            )}
          </div>

          <div>
            <Label htmlFor="displayName">{t("settings.displayName")}</Label>
            <TextInput
              id="displayName"
              name="displayName"
              value={form.displayName}
              onChange={handleChange}
              type="text"
            />
          </div>

          <div>
            <Label htmlFor="firstName">{t("settings.firstName")}</Label>
            <TextInput
              id="firstName"
              name="firstName"
              value={form.firstName}
              onChange={handleChange}
              type="text"
            />
          </div>

          <div>
            <Label htmlFor="lastName">{t("settings.lastName")}</Label>
            <TextInput
              id="lastName"
              name="lastName"
              value={form.lastName}
              onChange={handleChange}
              type="text"
            />
          </div>

          <div className="flex justify-center pt-4">
            <Button
              className="neon-btn neon-btn-light tracking-neon"
              type="submit"
            >
              {saving ? "Saving..." : t("settings.saveChangesButton")}
            </Button>
          </div>
        </form>
      )}
    </div>
  );
};

export default Settings;
