using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Diagnostics;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using System.Xml.Schema;
using Xamarin.Forms;

namespace Orar
{
    public partial class MainPage : ContentPage
    {
        public MainPage()
        {
            InitializeComponent();
            BindingContext = this;
        }
        protected override async void OnAppearing()
        {
            base.OnAppearing();
            CarouselMain.ItemsSource = await App.Database.GetZile();
        }
        protected override void OnDisappearing()
        {
            base.OnDisappearing();
            CarouselMain.ItemsSource = null;
        }
    }
}
