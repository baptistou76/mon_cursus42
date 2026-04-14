import { useState } from "react";
import {
  Button,
  Label,
  TextInput,
  Toast,
  ToastToggle,
  HelperText,
} from "flowbite-react";
import { useAuth } from "../context/AuthContext";
import { HiCheck, HiExclamation } from "react-icons/hi";
import { useNavigate } from "react-router";
import { useTranslation } from "react-i18next";

export default function Register() {
  const { user, localRegister } = useAuth();
  const navigate = useNavigate();
  const { t } = useTranslation();

  const [formData, setFormData] = useState({
    email: "",
    password: "",
    confirmPassword: "",
    displayName: "",
    firstName: "",
    lastName: "",
  });

  const [error, setError] = useState("");
  const [success, setSuccess] = useState(false);
  const [isSubmitting, setIsSubmitting] = useState(false);

  const handleChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    setFormData({
      ...formData,
      [e.target.name]: e.target.value,
    });
  };

  const passwordRules = [
    {
      test: (p: string) => p.length >= 8,
      message: `${t("registration.passwordRequirementsLength")}`,
    },
    {
      test: (p: string) => /[A-Z]/.test(p),
      message: `${t("registration.passwordRequirementsUppercase")}`,
    },
    {
      test: (p: string) => /[a-z]/.test(p),
      message: `${t("registration.passwordRequirementsLowercase")}`,
    },
    {
      test: (p: string) => /[0-9]/.test(p),
      message: `${t("registration.passwordRequirementsNumber")}`,
    },
    {
      test: (p: string) => /[!@#$%^&*(),.?":{}|<>\\[\]\/\\;`~_\-+=]/.test(p),
      message: `${t("registration.passwordRequirementsSpecial")}`,
    },
  ];

  const validatePassword = (password: string) => {
    const failed = passwordRules
      .filter((rule) => !rule.test(password))
      .map((rule) => rule.message);
    return {
      valid: failed.length === 0,
      failed,
    };
  };

  const handleSubmit = async (event: React.FormEvent) => {
    event.preventDefault();
    setError("");
    setIsSubmitting(true);

    if (formData.password !== formData.confirmPassword) {
      setError("Passwords do not match");
      setIsSubmitting(false);
      return;
    }

    const { valid, failed } = validatePassword(formData.password);
    if (!valid) {
      setError(
        `${t("registration.passwordRequirementsError")} ${failed.join(", ")}`,
      );
      setIsSubmitting(false);
      return;
    }

    try {
      await localRegister(
        formData.email,
        formData.password,
        formData.displayName,
        formData.firstName,
        formData.lastName,
      );

      setSuccess(true);
      setTimeout(() => {
        navigate("/");
      }, 2000);
    } catch (error: any) {
      setError(error.message);
    } finally {
      setIsSubmitting(false);
    }
  };

  return (
    <div className="flex min-h-screen flex-col content-center items-center justify-center px-4 sm:px-6 lg:px-8 py-4 sm:py-6">
      <h2 className="pb-4 text-2xl font-bold">{t("registration.head")}</h2>

      {user && <p>User is registered</p>}

      {/* Success Toast */}
      {success && (
        <div className="mb-4">
          <Toast>
            <div className="inline-flex h-8 w-8 shrink-0 items-center justify-center rounded-lg bg-green-100 text-green-500 dark:bg-green-800 dark:text-green-200">
              <HiCheck className="h-5 w-5" />
            </div>
            <div className="ml-3 text-sm font-normal">{t("toast.Success")}</div>
            <ToastToggle />
          </Toast>
        </div>
      )}

      {/* Error Toast */}
      {error && (
        <div className="mb-4">
          <Toast>
            <div className="inline-flex h-8 w-8 shrink-0 items-center justify-center rounded-lg bg-red-100 text-red-500 dark:bg-red-700 dark:text-red-200">
              <HiExclamation className="h-5 w-5" />
            </div>
            <div className="ml-3 text-sm font-normal">
              {t("toast.Error")}
              {error}
            </div>
            <ToastToggle onDismiss={() => setError("")} />
          </Toast>
        </div>
      )}

      {!user && (
        <form onSubmit={handleSubmit} className="flex w-full max-w-md flex-col gap-4">
          <div>
            <Label htmlFor="displayName">{t("registration.displayName")}</Label>
            <TextInput
              id="displayName"
              name="displayName"
              type="text"
              placeholder={t("registration.displayNamePlaceholder")}
              value={formData.displayName}
              onChange={handleChange}
              required
              shadow
              disabled={isSubmitting}
            />
          </div>

          <div>
            <Label htmlFor="email">Email *</Label>
            <TextInput
              id="email"
              name="email"
              type="email"
              placeholder="login@student.42lehavre.fr"
              value={formData.email}
              onChange={handleChange}
              required
              shadow
              disabled={isSubmitting}
            />
          </div>

          <div>
            <Label htmlFor="firstName">{t("registration.firstName")}</Label>
            <TextInput
              id="firstName"
              name="firstName"
              type="text"
              placeholder={t("registration.firstNamePlaceholder")}
              value={formData.firstName}
              onChange={handleChange}
              shadow
              disabled={isSubmitting}
            />
          </div>

          <div>
            <Label htmlFor="lastName">{t("registration.lastName")}</Label>
            <TextInput
              id="lastName"
              name="lastName"
              type="text"
              placeholder={t("registration.lastNamePlaceholder")}
              value={formData.lastName}
              onChange={handleChange}
              shadow
              disabled={isSubmitting}
            />
          </div>

          <div>
            <Label htmlFor="password">{t("registration.password")}</Label>
            <TextInput
              id="password"
              name="password"
              type="password"
              placeholder={t("registration.passwordPlaceholder")}
              value={formData.password}
              onChange={handleChange}
              required
              shadow
              disabled={isSubmitting}
            />
            <HelperText className="mt-1">
              {t("registration.passwordRequirements")}
              <ul className="list-inside list-disc">
                {passwordRules.map((rule, index) => (
                  <li key={index}>{rule.message}</li>
                ))}
              </ul>
            </HelperText>
          </div>

          <div>
            <Label htmlFor="confirmPassword">
              {t("registration.confirmPassword")}
            </Label>
            <TextInput
              id="confirmPassword"
              name="confirmPassword"
              type="password"
              placeholder={t("registration.confirmPasswordPlaceholder")}
              value={formData.confirmPassword}
              onChange={handleChange}
              required
              shadow
              disabled={isSubmitting}
            />
          </div>

          <div className="flex justify-center pt-4">
            <Button
              className="neon-btn neon-btn-light tracking-neon"
              type="submit"
              disabled={isSubmitting}
            >
              {isSubmitting
                ? t("registration.creatingAccount")
                : t("registration.registerAccount")}
            </Button>
          </div>
        </form>
      )}
    </div>
  );
}
